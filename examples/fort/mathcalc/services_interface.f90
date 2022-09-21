module services_interface
implicit none

interface 

function run_server(address) bind(C, NAME="RunServer")
use, intrinsic:: iso_c_binding, only: c_char, c_ptr
character(kind=c_char), intent(in) :: address
type(c_ptr) :: run_server
end function

!subroutine run_server(address) bind(C, NAME="RunServer")
!use, intrinsic:: iso_c_binding, only: c_char
!character(kind=c_char), intent(in) :: address
!end subroutine

subroutine server_handler(server) bind(C, NAME="ServerHandler")
use, intrinsic:: iso_c_binding, only : c_ptr
type(c_ptr) :: server
end subroutine

subroutine destroy_server(server) bind(C, NAME="DestroyServer")
use, intrinsic:: iso_c_binding, only : c_ptr
type(c_ptr) :: server
end subroutine

end interface

end module
