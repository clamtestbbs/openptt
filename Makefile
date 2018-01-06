#We can use this line again when innbbsd is fixed
#SUBDIR=	mbbsd util innbbsd

SUBDIR=	mbbsd util 
BBSHOME?=$(HOME)

all install clean:
	@for i in $(SUBDIR); do\
		cd $$i;\
		make BBSHOME=$(BBSHOME) OSTYPE=$(OSTYPE) $@;\
		cd ..;\
	done
