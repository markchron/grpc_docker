program async_server
use, intrinsic:: iso_c_binding
use greeter_async
implicit none
character(80) :: address
address = "0.0.0.0:50051"//c_null_char

call run_server(address)

end program