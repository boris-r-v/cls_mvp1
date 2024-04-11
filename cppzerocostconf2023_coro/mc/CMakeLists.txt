# Targets greeter_[async_](client|server)
foreach(_target
    co2 co3 co4 co5 co6 co7 co8 )
    add_executable(${_target} "${_target}.cpp")
endforeach()

