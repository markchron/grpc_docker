program math_fort

use, intrinsic::iso_c_binding, only : c_ptr, c_null_char
use calc_mod
use services_interface 

implicit none

type(c_ptr) :: m_thread
character(80) :: address
integer :: i

address = '0.0.0.0:50051'//c_null_char
!m_server = run_server(address)
m_thread =  run_server(address)

!call server_handler(m_server)

do i=1, 3
    write(*, '(i5)') param
    call sleep(5)
    param = param + 5
end do

call destroy_server(m_thread)

end program