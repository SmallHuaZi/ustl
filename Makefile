include dir.mk
include ${__va_depends}

debug_enbale := true
CXXFLAGS = ${__include_path} -c

ifeq ($(debug_enbale),true)
CXXFLAGS += -g
endif

__va_depends :=$(addsuffix .d,$(basename debug.cpp)) # $(wildcard *.cpp)

__va_cpps := $(wildcard ${__impl_dir}/*.cpp)
__va_objs := $(notdir $(patsubst %.cpp,%.o,${__va_cpps}))

main: auto_dir debug.o FORCE
	make -C ${__impl_dir}/; \
	g++ ${__obj_dir}/*.o \
	-o ${__va_executable_dir}/$@ 

FORCE:

auto_dir:
	@if [ ! -d ${__va_executable_dir} ] ; \
	then mkdir ${__va_executable_dir} ; \
	fi; \
	if [ ! -d ${__va_libary_dir} ] ; \
	then mkdir ${__va_libary_dir} ; \
	fi; \
	if [ ! -d ${__slib_dir} ] ; \
	then mkdir ${__slib_dir} ; \
	fi; \
	if [ ! -d ${__dlib_dir} ] ; \
	then mkdir ${__dlib_dir} ; \
	fi;


%.d : %.cpp
	@g++ ${__include_path} -MM $^ > $@.tmp;\
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' <$@.tmp >$@;\
	rm -f $@.tmp

%.o : %.cpp
	@g++ ${__include_path} -c -o ${__obj_dir}/$@ $^ -g



.PHONY: clean
clean:
	rm -f ${__va_executable_dir}/main
	rm -f ${__obj_dir}/*.o
