a1:test2.o dberror.o storage_mgr.o
	gcc test2.o dberror.o storage_mgr.o -o output
dberror.o:dberror.c dberror.h
	gcc -c dberror.c
test2.o :test2.c test_helper.h dberror.h storage_mgr.h
			gcc -c test2.c
storage_mgr.o:storage_mgr.c storage_mgr.h dberror.h
	gcc -c storage_mgr.c
