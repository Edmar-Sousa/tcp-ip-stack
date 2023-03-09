compiler := gcc

headerdir := header
objdir := build
srcdir := src

objs := enlace.o


all:
	$(compiler) -c $(srcdir)/arp.c -I $(headerdir) -o $(objdir)/arp.o
	$(compiler) -c $(srcdir)/enlace.c -I $(headerdir) -o $(objdir)/enlace.o
	
	$(compiler) $(srcdir)/main.c $(objdir)/*.o -I $(headerdir) -o $(objdir)/main
