subroutine multiple(a, b, c)

use calc_mod

implicit none
integer, intent(in) :: a, b
integer, intent(out) :: c

c = a + b * param

end subroutine