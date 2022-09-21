
module greeter_async

implicit none

interface

subroutine run_server(address) bind(C, NAME='RunServer')
use, intrinsic:: iso_c_binding, only: c_char
character(kind=c_char), intent(in):: address(*) 
end subroutine

end interface

end module