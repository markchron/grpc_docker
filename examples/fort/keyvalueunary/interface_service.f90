module interface_service

implicit none
public 

interface

subroutine runserver() BIND(C, NAME="RunServer")
end subroutine

end interface

end module