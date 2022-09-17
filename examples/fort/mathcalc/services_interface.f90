module services_interface

implicit none

interface 
subroutine runserver() BIND(C, NAME="RunServer")
end subroutine
end interface

end module
