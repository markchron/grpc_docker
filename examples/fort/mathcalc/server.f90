program math_fort

use calc_mod
use services_interface 
implicit none

character(80) :: address
integer :: i
address = 'localhost:50051'//c_null_char

m_server = create_server_ptr(address)
!call initial_server(m_server)

do i=1, 30
    write(*, '(i5)') param
    call sleep(5)
    param = param + 5
end do

end program