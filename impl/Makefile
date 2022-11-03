__va_all_src := $(wildcard *.cpp)
__va_all_objs :=${__va_all_src:.cpp=.o}

${__va_all_objs} : ${__va_all_src}
	g++ ${__include_path} -c -o ${__obj_dir}/$@ $^ -g

