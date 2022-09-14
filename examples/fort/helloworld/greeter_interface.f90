module greeter_interface
implicit none
public 

interface
function RunServer() result(rn) bind(C)
use, intrinsic :: iso_c_binding, only: c_int
integer(c_int) :: rn
end function

end interface

end module