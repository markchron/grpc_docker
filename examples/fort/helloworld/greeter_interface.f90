module greeter_interface

implicit none

interface
subroutine RunServer() bind(C)
use, intrinsic :: iso_c_binding
end subroutine

end interface

end module