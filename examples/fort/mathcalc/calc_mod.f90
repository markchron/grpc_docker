module calc_mod

! Fortran 2003 and Later
use iso_c_binding

implicit none

integer :: param = 0

type(c_ptr) :: m_server = c_null_ptr

end module