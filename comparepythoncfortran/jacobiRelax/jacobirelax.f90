program main
  integer, parameter :: ssize = 2048
  real, dimension(ssize,ssize)::u
  real, dimension(ssize,ssize)::f
  real, dimension(ssize,ssize)::u_new
  real, dimension(ssize,ssize)::temp

  call zero(u)
  call zero(f)
  call zero(u_new)
  call random(u)
  do k=1, 10
    do i=2, 2047
      do j=2, 2047
        u_new(i,j) = 0.25*(h2*f(i,j) + u(i-1,j) + u(i+1,j) + u(i,j-1) + u(i,j+1))
      enddo
    enddo
    write (*,*) "Iter ", k, "max= ",maxval(u_new)
    temp = u
    u = u_new
    u_new = u
  enddo 

end program

subroutine zero(array)
  real, dimension(2048,2048)::array
  do i=1, 2048
    do j=1, 2048
      array(i,j)=0.0
    enddo
  enddo

end subroutine zero

subroutine random(array)
  real, dimension(2048,2048)::array
  do i=2,2047
    do j=2, 2047
      array(i,j) = rand()
    enddo
  enddo
end subroutine random

subroutine maximum(array)
  real, dimension(2048,2048)::array
  real :: maxi = 0.0
  do i=1, 2048
    do j=1, 2048
      if(array(i,j).gt.maxi) then
        maxi=array(i,j)
      end if
    end do
  end do
  write (*,*) "max=", maxi
end subroutine maximum
