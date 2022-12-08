__cpp_files = ${wildcard *.cpp}
__objects = ${patsubst %.cpp,%.o,${__cpp_files}} 

main : ${__objects}
	@echo ${__cpp_files}
	@echo Impl Dictionary Complied

%.o : %.cpp	
	${CXX} ${CXXFLAGS} $< -o ${__obj_dir}/$@ 