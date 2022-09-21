module calc_mod
use, intrinsic :: iso_c_binding, only : c_ptr, c_null_ptr
implicit none

integer :: param = 0
type(c_ptr) :: m_server = c_null_ptr

end module