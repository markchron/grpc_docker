subroutine rise_operates(num)
use keyvalue_mod
implicit none
integer, value, intent(in) :: num
operation  = operation + num
end subroutine

function get_operates() result(val)
use keyvalue_mod
implicit none
integer :: val
val = operation
end function