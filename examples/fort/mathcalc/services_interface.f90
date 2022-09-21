module services_interface
use, intrinsic :: iso_c_binding
implicit none

interface 

! subroutine runserver() BIND(C, NAME="RunServer")
! end subroutine

function create_server_ptr(url) bind(C, NAME="CreateServerPtr")
use, intrinsic :: iso_c_binding, only: c_ptr, c_char
character(kind=c_char), intent(in) :: url(*)
type(c_ptr) :: create_server_ptr
end function

subroutine initial_server(server) bind(C, NAME="InitialServer")
use, intrinsic :: iso_c_binding, only : c_ptr
type(c_ptr) :: server
end subroutine

end interface

end module
