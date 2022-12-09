__cpp_files = ${wildcard *.cpp}
__objects = ${patsubst %.cpp,%.o,${__cpp_files}} 

main : ${__objects}
	ar crv ${__va_slib} ${__obj_dir}/*.o

%.o : %.cpp	
	${CXX} ${CXXFLAGS} $< -o ${__obj_dir}/$@ 