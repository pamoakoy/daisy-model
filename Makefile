# Makefile --- For maintaining the Daisy project.
#
# Automatic creation of daisy on multiple platforms.
#
# You need GNU Make for using this file.
#
# The following envirnoment variables are used:
#
# HOSTTYPE
#	sun4	Create code for Solaris-2 / UltraSPARC.
#	hp	Create code for HP/UX / HP-PA.
#	i386	Create code for Win32 / Pentium.

# All makefiles should have these.
#
SHELL = /bin/sh
MAKEFLAGS =

# HOSTTYPE is not defined in the native win32 Emacs.
#
ifeq ($(OS),Windows_NT)
	HOSTTYPE = i386
endif

# Set USE_OPTIMIZE to `true' if you want a fast executable.
#
#USE_OPTIMIZE = true
USE_OPTIMIZE = false

# Set USE_PROFILE if you want to profile the executable
#
#USE_PROFILE = true
USE_PROFILE = false

# Set COMPILER according to which compiler you use.
#	sun		Use the unbundled sun compiler.
#	gnu		Use the standard GNU compiler.
#	egcs		Use the experimental GNU compiler.
#	borland		Use the Borland compiler.
ifeq ($(HOSTTYPE),sun4)
	COMPILER = egcs
#	COMPILER = gnu
#	COMPILER = sun	
endif
ifeq ($(HOSTTYPE),hp)
	COMPILER = gnu
endif
ifeq ($(HOSTTYPE),i386)
	COMPILER = borland
endif

# On SPARC platforms we trap mathematical exception with some assembler code.
#
ifeq ($(HOSTTYPE),sun4) 
	SPARCSRC = set_exceptions.S
	SPARCOBJ = set_exceptions.o
endif

# Find the profile flags.
#
ifeq ($(USE_PROFILE),true)
	ifneq ($(COMPILER),borland)
		PROFILE = -pg
	endif
endif

# Find the optimize flags.
#
ifeq ($(USE_OPTIMIZE),true)
	ifeq ($(COMPILER),egcs)
		ifeq (($HOSTTYPE),sun4)
			OPTIMIZE = -O3 -ffast-math -mcpu=ultrasparc
		else
			OPTIMIZE = -O3 -ffast-math 
		endif
	endif
	ifeq ($(COMPILER),gnu)
		ifeq (($HOSTTYPE),sun4)
			OPTIMIZE = -O3 -ffast-math -mv8
		else
			OPTIMIZE = -O2
		endif
	endif
endif

# Create the right compile command.
#
ifeq ($(COMPILER),egcs)
	COMPILE = /pack/egcs/bin/c++ -W -Wall -Wstrict-prototypes -Wconversion -fno-exceptions -DEGCS -g -pipe -frepo
	#COMPILE = /pack/gcc-2.8.1/bin/c++ -W -Wall -Wstrict-prototypes -Wconversion -fno-exceptions -DEGCS -g -pipe -frepo
	CCOMPILE = gcc -I/pack/f2c/include -g -Wall

endif
ifeq ($(COMPILER),gnu)
	ifeq ($(HOSTTYPE),hp)
		COMPILE = c++ -Wall -pipe	#No repo, no debug.  So sad.
	else
		COMPILE = c++ -Wall -g -frepo -pipe
	endif
	CCOMPILE = gcc -I/pack/f2c/include -g -Wall
endif
ifeq ($(COMPILER),sun)
	COMPILE = /pack/devpro/SUNWspro/bin/CC
	CCOMPILE = gcc -I/pack/f2c/include -g -Wall
endif
ifeq ($(COMPILER),borland)
	COMPILE = /bc5/bin/bcc32 -P -v -wdef -wnod -wamb -w-par -w-hid
	CCOMPILE = /bc5/bin/bcc32 -P- -v -wdef -wnod -wamb -w-par -w-hid
endif

# Construct the compile command.
#
CC = $(COMPILE) $(OPTIMIZE) $(PROFILE)

# Find the rigth math library.
#
ifeq ($(HOSTTYPE),sun4)
	MATHLIB = -lm
endif
ifeq ($(HOSTTYPE),hp)
	MATHLIB = -lM
endif
ifeq ($(HOSTTYPE),i386)
	MATHLIB =
endif

# Locate the tk library.
#
TKINCLUDE	= -I/pack/tcl+tk-8/include -I/usr/openwin/include
TKLIB	  	= -L/pack/tcl+tk-8/lib -L/usr/openwin/lib \
		  -ltix4.1.8.0 -ltk8.0 -ltcl8.0 -lX11 -lsocket -lnsl -ldl

# Find the right file extension.
#
ifeq ($(HOSTTYPE),i386)
	OBJ = .obj
	EXT = .exe
else
	OBJ = .o
	EXT =
endif

# Figure out how to link.
#
ifeq ($(COMPILER),borland)
	LINK =    /bc5/bin/tlink32 /v -Tpe -ap -c -x -e
	DLLLINK = /bc5/bin/bcc32 -P- -v -lw-dup -WDE -lTpd -lv -e
	NOLINK = -c
	CRTLIB = C:\BC5\LIB\c0x32.obj
else
	LINK = $(CC) -o
	NOLINK = -c
endif

# Select the C files that doesn't have a corresponding header file.
# These are all components of some library.
#
COMPONENTS = filter_array.C filter_all.C filter_none.C filter_some.C \
	column_std.C  weather_simple.C uzrichard.C \
	hydraulic_yolo.C hydraulic_M_vG.C hydraulic_B_vG.C hydraulic_M_C.C \
	hydraulic_B_C.C hydraulic_M_BaC.C hydraulic_B_BaC.C \
	groundwater_static.C horizon_std.C \
	crop_std.C action_sow.C action_stop.C condition_time.C \
	condition_logic.C log_file.C action_irrigate.C action_lisp.C \
	weather_none.C action_fertilize.C weather_file.C action_tillage.C \
	action_harvest.C hydraulic_old.C crop_old.C crop_sold.C \
	action_with.C hydraulic_old2.C nitrification_soil.C \
	nitrification_solute.C hydraulic_mod_C.C uzlr.C transport_cd.C \
	transport_none.C transport_convection.C adsorbtion_vS_S.C \
	adsorbtion_none.C tortuosity_M_Q.C tortuosity_linear.C \
	adsorbtion_freundlich.C adsorbtion_linear.C adsorbtion_langmuir.C \
	filter_checkpoint.C

# Select the C files with a corresponding header file from the library.
#
INTERFACES = daisy.C parser.C log.C weather.C column.C crop.C \
	alist.C syntax.C library.C action.C condition.C horizon.C \
	filter.C csmp.C time.C uzmodel.C parser_file.C hydraulic.C \
	soil.C mathlib.C bioclimate.C surface.C soil_water.C \
	soil_NH4.C soil_NO3.C organic_matter.C nitrification.C \
	denitrification.C soil_heat.C groundwater.C snow.C solute.C \
	am.C im.C om.C harvest.C options.C geometry.C transport.C \
	librarian.C cdaisy.C adsorbtion.C tortuosity.C event.C eventqueue.C \
	minimanager.C printer.C printer_file.C

# Select the C files that are not part of the library.
#
MAIN = main.C tkmain.C

# The object files used in the daisy library.
#
LIBOBJ = $(COMPONENTS:.C=${OBJ}) $(INTERFACES:.C=${OBJ}) $(SPARCOBJ)

# Find all object files, header files, and source files.
#
OBJECTS = $(LIBOBJ) $(MAIN:.C=${OBJ}) cmain${OBJ}
SOURCES = $(COMPONENTS) $(INTERFACES) $(SPARCSRC) $(MAIN) cmain.c
HEADERS = $(INTERFACES:.C=.h) common.h version.h

# Find all printable files.
#
TEXT =  Makefile ChangeLog TODO $(HEADERS) $(SOURCES) 

# The executables.
#
EXECUTABLES = daisy${EXT} tkdaisy${EXT} cdaisy${EXT}

# Select files to be removed by the next cvs update.
#
REMOVE = mike_she.h mike_she.C

# These are the file extensions we deal with.
# 
.SUFFIXES:	.C ${OBJ} .h .c ${EXT} .a

# Create all the executables.
#
all:	$(EXECUTABLES)

# Create the main executable.
#
daisy${EXT}:	main${OBJ} $(FORLIB) $(LIBOBJ)
	$(LINK)daisy $(CRTLIB) $^ $(MATHLIB)

# Create manager test executable.
#
mandaisy${EXT}:	manmain${OBJ} $(FORLIB) $(LIBOBJ)
	$(LINK)mandaisy $(CRTLIB) $^ $(MATHLIB)

# Create bug test executable.
#
bugdaisy${EXT}:	bugmain${OBJ} $(FORLIB) $(LIBOBJ)
	$(LINK)bugdaisy $(CRTLIB) $^ $(MATHLIB)

# Create executable with embedded tcl/tk.
#
tkdaisy${EXT}:	tkmain${OBJ} $(FORLIB) $(LIBOBJ)
	$(LINK)tkdaisy $^ $(TKLIB) $(MATHLIB)

# Create the C main file.
#
cdaisy${EXT}:  cmain${OBJ} $(FORLIB) $(LIBOBJ)
	$(LINK)cdaisy $^ $(MATHLIB)

# Create a DLL.
#
daisy.dll:	$(LIBOBJ)
#	/bc5/bin/tlink32 /Tpd /v $^, daisy.dll,, cw32i.lib
	$(DLLLINK)daisy.dll $^ $(MATHLIB)


dlldaisy${EXT}:	cmain${OBJ} daisy.dll
	$(LINK)dlldaisy $^ $(MATHLIB)


# Count the size of daisy.
#
wc: $(HEADERS) $(SOURCES) 
	wc -l $(TEXT) | sort -nr

wc-h: $(HEADERS)
	wc -l $(HEADERS)

wc-s: $(SOURCES)
	wc -l $(SOURCES)

# Update the TAGS table.
#
tags: TAGS

TAGS: $(SOURCES) $(HEADERS)
	etags $(SOURCES) $(HEADERS)

# Fix DOS newline breakage.
#
dos2unix:
	perl -pi.bak -e 's/\r\n$$/\n/' $(TEXT)

# This prints all the text files when called on Solaris 1.
#
print:
	mp -p /home/user_13/fischer/bin/mp.pro.none -a4 $(TEXT) | parr -s | up -n pup | lpr -Pduplex


# Print the current syntax for the Daisy input language.
#
dump:	daisy
	daisy -p

# Various test targets.
#
xtest:	test/test.dai daisy
	(cd test; ../daisy test.dai)

bless:
	(cd test; make bless )

water-test:	daisy 
	(cd test; make water-test )

crop-test:	daisy 
	(cd test; make crop-test )

evapo-test:	daisy 
	(cd test; make evapo-test )

balance:	daisy
	(cd test; make balance)

check:	daisy
	(cd karup; make check )

# Remove all the temporary files.
#
clean:
	rm $(OBJECTS) *.rpo $(EXECUTABLES) *.obj *.exe *.o *~

# Update the Makefile when dependencies have changed.
#
depend: $(SOURCES) 
	rm -f Makefile.old
	mv Makefile Makefile.old
	sed -e '/^# AUTOMATIC/q' < Makefile.old > Makefile
	/pack/egcs/bin/c++ -DEGCS -I. $(TKINCLUDE) -MM $(SOURCES) \
		| sed -e 's/\.o:/$${OBJ}:/' >> Makefile

# Create a ZIP file with all the sources.
#
daisy-src.zip:	$(TEXT)
	rm -f daisy-src.zip
	zip daisy-src.zip $(TEXT) daisy.ide

# Move it to ftp.
#
dist:	cvs
	$(MAKE) daisy-src.zip
	mv -f daisy-src.zip $(HOME)/.public_ftp/daisy/

# Update the CVS repository.
#
cvs: $(TEXT)
	@if [ "X$(TAG)" = "X" ]; then echo "*** No tag ***"; exit 1; fi
	rm -f version.h
	echo "// version.h -- automatically generated file" > version.h
	echo " " >> version.h
	echo "static const char *const version = \"$(TAG)\";" >> version.h
	mv ChangeLog ChangeLog.old
	echo `date "+%Y-%m-%d "` \
	     " Per Abrahamsen  <abraham@dina.kvl.dk>" > ChangeLog
	echo >> ChangeLog
	echo "	* Version" $(TAG) released. >> ChangeLog
	echo >> ChangeLog
	cat ChangeLog.old >> ChangeLog
	(cd lib; $(MAKE) cvs);
	-cvs add $(TEXT)
	rm -f $(REMOVE) 
	-cvs remove $(REMOVE) 
	cvs commit -m "Version $(TAG)"
	cvs tag release_`echo $(TAG) | sed -e 's/[.]/_/g'`

# How to compile the assembler file.
#
set_exceptions${OBJ}: set_exceptions.S
	as -o set_exceptions${OBJ} set_exceptions.S

# How to compile a C++ file.
#
.C${OBJ}:
	$(CC) $(NOLINK) $<

# How to compile a C file.
#
.c${OBJ}:
	$(CCOMPILE) $(OPTIMIZE) $(PROFILE) $(NOLINK) $<

# There is a bug when egcs compile snow.C with optimization.
#
ifeq ($(COMPILER),egcs)
ifeq ($(USE_OPTIMIZE),true)

snow.o: snow.C
	$(COMPILE) $(PROFILE) $(NOLINK) $<

endif
endif

# Special rule for tkmain.o
#
tkmain${OBJ}: tkmain.C
	$(CC) $(TKINCLUDE) $(NOLINK) $<

############################################################
# AUTOMATIC -- DO NOT CHANGE THIS LINE OR ANYTHING BELOW IT!
filter_array${OBJ}: filter_array.C filter.h librarian.h library.h common.h \
 alist.h syntax.h geometry.h
filter_all${OBJ}: filter_all.C filter.h librarian.h library.h common.h \
 alist.h syntax.h
filter_none${OBJ}: filter_none.C filter.h librarian.h library.h common.h \
 alist.h syntax.h
filter_some${OBJ}: filter_some.C filter.h librarian.h library.h common.h \
 alist.h syntax.h
column_std${OBJ}: column_std.C column.h librarian.h library.h common.h \
 alist.h syntax.h crop.h bioclimate.h surface.h uzmodel.h im.h soil.h \
 horizon.h hydraulic.h tortuosity.h geometry.h soil_water.h \
 soil_heat.h soil_NH4.h solute.h adsorbtion.h soil_NO3.h \
 organic_matter.h nitrification.h denitrification.h groundwater.h \
 log.h filter.h am.h
weather_simple${OBJ}: weather_simple.C weather.h librarian.h library.h \
 common.h alist.h syntax.h im.h log.h filter.h
uzrichard${OBJ}: uzrichard.C uzmodel.h librarian.h library.h common.h \
 alist.h syntax.h soil.h horizon.h hydraulic.h tortuosity.h geometry.h \
 mathlib.h filter.h log.h
hydraulic_yolo${OBJ}: hydraulic_yolo.C hydraulic.h librarian.h library.h \
 common.h alist.h syntax.h csmp.h
hydraulic_M_vG${OBJ}: hydraulic_M_vG.C hydraulic.h librarian.h library.h \
 common.h alist.h syntax.h csmp.h
hydraulic_B_vG${OBJ}: hydraulic_B_vG.C hydraulic.h librarian.h library.h \
 common.h alist.h syntax.h csmp.h
hydraulic_M_C${OBJ}: hydraulic_M_C.C hydraulic.h librarian.h library.h \
 common.h alist.h syntax.h
hydraulic_B_C${OBJ}: hydraulic_B_C.C hydraulic.h librarian.h library.h \
 common.h alist.h syntax.h
hydraulic_M_BaC${OBJ}: hydraulic_M_BaC.C hydraulic.h librarian.h library.h \
 common.h alist.h syntax.h
hydraulic_B_BaC${OBJ}: hydraulic_B_BaC.C hydraulic.h librarian.h library.h \
 common.h alist.h syntax.h
groundwater_static${OBJ}: groundwater_static.C groundwater.h uzmodel.h \
 librarian.h library.h common.h alist.h syntax.h
horizon_std${OBJ}: horizon_std.C horizon.h librarian.h library.h common.h \
 alist.h syntax.h
crop_std${OBJ}: crop_std.C crop.h time.h common.h log.h filter.h \
 librarian.h library.h alist.h syntax.h csmp.h bioclimate.h column.h \
 soil_water.h soil.h horizon.h hydraulic.h tortuosity.h geometry.h \
 om.h organic_matter.h soil_heat.h soil_NH4.h solute.h adsorbtion.h \
 soil_NO3.h am.h harvest.h mathlib.h
action_sow${OBJ}: action_sow.C action.h common.h daisy.h column.h \
 librarian.h library.h alist.h syntax.h crop.h
action_stop${OBJ}: action_stop.C action.h common.h syntax.h alist.h \
 daisy.h
condition_time${OBJ}: condition_time.C condition.h librarian.h library.h \
 common.h alist.h syntax.h daisy.h
condition_logic${OBJ}: condition_logic.C condition.h librarian.h library.h \
 common.h alist.h syntax.h
log_file${OBJ}: log_file.C log.h filter.h librarian.h library.h common.h \
 alist.h syntax.h condition.h csmp.h
action_irrigate${OBJ}: action_irrigate.C action.h common.h daisy.h \
 weather.h librarian.h library.h alist.h syntax.h im.h column.h am.h
action_lisp${OBJ}: action_lisp.C action.h common.h daisy.h column.h \
 librarian.h library.h alist.h syntax.h condition.h
weather_none${OBJ}: weather_none.C weather.h librarian.h library.h \
 common.h alist.h syntax.h im.h
action_fertilize${OBJ}: action_fertilize.C action.h common.h daisy.h \
 column.h librarian.h library.h alist.h syntax.h am.h im.h
weather_file${OBJ}: weather_file.C weather.h librarian.h library.h \
 common.h alist.h syntax.h im.h options.h log.h filter.h
action_tillage${OBJ}: action_tillage.C action.h common.h daisy.h weather.h \
 librarian.h library.h alist.h syntax.h im.h column.h
action_harvest${OBJ}: action_harvest.C action.h common.h daisy.h column.h \
 librarian.h library.h alist.h syntax.h
hydraulic_old${OBJ}: hydraulic_old.C hydraulic.h librarian.h library.h \
 common.h alist.h syntax.h options.h mathlib.h csmp.h
crop_old${OBJ}: crop_old.C crop.h time.h common.h log.h filter.h \
 librarian.h library.h alist.h syntax.h csmp.h bioclimate.h column.h \
 soil_water.h soil.h horizon.h hydraulic.h tortuosity.h geometry.h \
 om.h organic_matter.h soil_heat.h soil_NH4.h solute.h adsorbtion.h \
 soil_NO3.h am.h harvest.h mathlib.h
crop_sold${OBJ}: crop_sold.C crop.h time.h common.h log.h filter.h \
 librarian.h library.h alist.h syntax.h csmp.h bioclimate.h column.h \
 soil_water.h soil.h horizon.h hydraulic.h tortuosity.h geometry.h \
 organic_matter.h om.h soil_heat.h soil_NH4.h solute.h adsorbtion.h \
 soil_NO3.h am.h harvest.h mathlib.h
action_with${OBJ}: action_with.C action.h common.h daisy.h syntax.h \
 alist.h column.h librarian.h library.h
hydraulic_old2${OBJ}: hydraulic_old2.C hydraulic.h librarian.h library.h \
 common.h alist.h syntax.h options.h mathlib.h csmp.h
nitrification_soil${OBJ}: nitrification_soil.C nitrification.h librarian.h \
 library.h common.h alist.h syntax.h soil.h horizon.h hydraulic.h \
 tortuosity.h geometry.h soil_water.h soil_heat.h soil_NH4.h solute.h \
 adsorbtion.h soil_NO3.h csmp.h mathlib.h log.h filter.h groundwater.h \
 uzmodel.h
nitrification_solute${OBJ}: nitrification_solute.C nitrification.h \
 librarian.h library.h common.h alist.h syntax.h soil.h horizon.h \
 hydraulic.h tortuosity.h geometry.h soil_water.h soil_heat.h \
 soil_NH4.h solute.h adsorbtion.h soil_NO3.h csmp.h log.h filter.h \
 mathlib.h groundwater.h uzmodel.h
hydraulic_mod_C${OBJ}: hydraulic_mod_C.C hydraulic.h librarian.h library.h \
 common.h alist.h syntax.h
uzlr${OBJ}: uzlr.C uzmodel.h librarian.h library.h common.h alist.h \
 syntax.h soil.h horizon.h hydraulic.h tortuosity.h geometry.h log.h \
 filter.h mathlib.h
transport_cd${OBJ}: transport_cd.C transport.h librarian.h library.h \
 common.h alist.h syntax.h soil.h horizon.h hydraulic.h tortuosity.h \
 geometry.h soil_water.h solute.h adsorbtion.h log.h filter.h \
 mathlib.h
transport_none${OBJ}: transport_none.C transport.h librarian.h library.h \
 common.h alist.h syntax.h soil.h horizon.h hydraulic.h tortuosity.h \
 geometry.h soil_water.h solute.h adsorbtion.h log.h filter.h \
 mathlib.h
transport_convection${OBJ}: transport_convection.C transport.h librarian.h \
 library.h common.h alist.h syntax.h soil.h horizon.h hydraulic.h \
 tortuosity.h geometry.h soil_water.h solute.h adsorbtion.h log.h \
 filter.h mathlib.h
adsorbtion_vS_S${OBJ}: adsorbtion_vS_S.C adsorbtion.h librarian.h \
 library.h common.h alist.h syntax.h soil.h horizon.h hydraulic.h \
 tortuosity.h geometry.h mathlib.h
adsorbtion_none${OBJ}: adsorbtion_none.C adsorbtion.h librarian.h \
 library.h common.h alist.h syntax.h
tortuosity_M_Q${OBJ}: tortuosity_M_Q.C tortuosity.h librarian.h library.h \
 common.h alist.h syntax.h hydraulic.h
tortuosity_linear${OBJ}: tortuosity_linear.C tortuosity.h librarian.h \
 library.h common.h alist.h syntax.h hydraulic.h
adsorbtion_freundlich${OBJ}: adsorbtion_freundlich.C adsorbtion.h \
 librarian.h library.h common.h alist.h syntax.h soil.h horizon.h \
 hydraulic.h tortuosity.h geometry.h mathlib.h
adsorbtion_linear${OBJ}: adsorbtion_linear.C adsorbtion.h librarian.h \
 library.h common.h alist.h syntax.h soil.h horizon.h hydraulic.h \
 tortuosity.h geometry.h
adsorbtion_langmuir${OBJ}: adsorbtion_langmuir.C adsorbtion.h librarian.h \
 library.h common.h alist.h syntax.h soil.h horizon.h hydraulic.h \
 tortuosity.h geometry.h mathlib.h
filter_checkpoint${OBJ}: filter_checkpoint.C filter.h librarian.h \
 library.h common.h alist.h syntax.h
daisy${OBJ}: daisy.C daisy.h common.h weather.h librarian.h library.h \
 alist.h syntax.h im.h groundwater.h uzmodel.h horizon.h log.h \
 filter.h parser.h am.h nitrification.h hydraulic.h crop.h column.h \
 harvest.h action.h condition.h
parser${OBJ}: parser.C parser.h common.h syntax.h alist.h library.h
log${OBJ}: log.C log.h filter.h librarian.h library.h common.h alist.h \
 syntax.h
weather${OBJ}: weather.C weather.h librarian.h library.h common.h alist.h \
 syntax.h im.h mathlib.h
column${OBJ}: column.C column.h librarian.h library.h common.h alist.h \
 syntax.h
crop${OBJ}: crop.C crop.h time.h common.h syntax.h alist.h library.h
alist${OBJ}: alist.C csmp.h library.h common.h alist.h syntax.h
syntax${OBJ}: syntax.C syntax.h common.h alist.h library.h
library${OBJ}: library.C library.h common.h alist.h syntax.h
action${OBJ}: action.C action.h common.h syntax.h alist.h library.h
condition${OBJ}: condition.C condition.h librarian.h library.h common.h \
 alist.h syntax.h
horizon${OBJ}: horizon.C horizon.h librarian.h library.h common.h alist.h \
 syntax.h csmp.h hydraulic.h mathlib.h
filter${OBJ}: filter.C filter.h librarian.h library.h common.h alist.h \
 syntax.h
csmp${OBJ}: csmp.C csmp.h
time${OBJ}: time.C time.h common.h
uzmodel${OBJ}: uzmodel.C uzmodel.h librarian.h library.h common.h alist.h \
 syntax.h
parser_file${OBJ}: parser_file.C parser_file.h parser.h common.h options.h \
 syntax.h alist.h library.h csmp.h log.h filter.h librarian.h
hydraulic${OBJ}: hydraulic.C hydraulic.h librarian.h library.h common.h \
 alist.h syntax.h csmp.h
soil${OBJ}: soil.C soil.h horizon.h librarian.h library.h common.h alist.h \
 syntax.h hydraulic.h tortuosity.h geometry.h mathlib.h
mathlib${OBJ}: mathlib.C mathlib.h common.h
bioclimate${OBJ}: bioclimate.C bioclimate.h column.h librarian.h library.h \
 common.h alist.h syntax.h surface.h uzmodel.h im.h weather.h crop.h \
 csmp.h soil.h horizon.h hydraulic.h tortuosity.h geometry.h snow.h \
 log.h filter.h
surface${OBJ}: surface.C surface.h uzmodel.h librarian.h library.h \
 common.h alist.h syntax.h im.h soil_water.h log.h filter.h am.h \
 mathlib.h
soil_water${OBJ}: soil_water.C soil_water.h common.h log.h filter.h \
 librarian.h library.h alist.h syntax.h uzmodel.h soil.h horizon.h \
 hydraulic.h tortuosity.h geometry.h surface.h im.h groundwater.h \
 mathlib.h
soil_NH4${OBJ}: soil_NH4.C soil_NH4.h solute.h adsorbtion.h librarian.h \
 library.h common.h alist.h syntax.h soil_water.h soil.h horizon.h \
 hydraulic.h tortuosity.h geometry.h mathlib.h
soil_NO3${OBJ}: soil_NO3.C soil_NO3.h solute.h adsorbtion.h librarian.h \
 library.h common.h alist.h syntax.h soil_water.h soil.h horizon.h \
 hydraulic.h tortuosity.h geometry.h
organic_matter${OBJ}: organic_matter.C organic_matter.h syntax.h common.h \
 alist.h log.h filter.h librarian.h library.h am.h om.h soil.h \
 horizon.h hydraulic.h tortuosity.h geometry.h soil_water.h soil_NH4.h \
 solute.h adsorbtion.h soil_NO3.h soil_heat.h groundwater.h uzmodel.h \
 mathlib.h csmp.h
nitrification${OBJ}: nitrification.C nitrification.h librarian.h library.h \
 common.h alist.h syntax.h
denitrification${OBJ}: denitrification.C denitrification.h common.h \
 alist.h syntax.h soil.h horizon.h librarian.h library.h hydraulic.h \
 tortuosity.h geometry.h soil_water.h soil_heat.h organic_matter.h \
 soil_NO3.h solute.h adsorbtion.h groundwater.h uzmodel.h csmp.h log.h \
 filter.h
soil_heat${OBJ}: soil_heat.C soil_heat.h alist.h common.h surface.h \
 uzmodel.h librarian.h library.h syntax.h im.h groundwater.h weather.h \
 soil_water.h soil.h horizon.h hydraulic.h tortuosity.h geometry.h \
 mathlib.h log.h filter.h
groundwater${OBJ}: groundwater.C groundwater.h uzmodel.h librarian.h \
 library.h common.h alist.h syntax.h
snow${OBJ}: snow.C snow.h alist.h common.h syntax.h log.h filter.h \
 librarian.h library.h soil.h horizon.h hydraulic.h tortuosity.h \
 geometry.h soil_water.h soil_heat.h mathlib.h
solute${OBJ}: solute.C solute.h adsorbtion.h librarian.h library.h \
 common.h alist.h syntax.h log.h filter.h soil.h horizon.h hydraulic.h \
 tortuosity.h geometry.h soil_water.h mathlib.h transport.h
am${OBJ}: am.C am.h common.h om.h im.h syntax.h alist.h log.h filter.h \
 librarian.h library.h geometry.h mathlib.h
im${OBJ}: im.C im.h log.h filter.h librarian.h library.h common.h alist.h \
 syntax.h
om${OBJ}: om.C om.h common.h syntax.h alist.h geometry.h log.h filter.h \
 librarian.h library.h mathlib.h
harvest${OBJ}: harvest.C harvest.h time.h common.h syntax.h log.h filter.h \
 librarian.h library.h alist.h
options${OBJ}: options.C options.h common.h
geometry${OBJ}: geometry.C geometry.h common.h syntax.h alist.h mathlib.h
transport${OBJ}: transport.C transport.h librarian.h library.h common.h \
 alist.h syntax.h
librarian${OBJ}: librarian.C librarian.h library.h common.h alist.h \
 syntax.h
cdaisy${OBJ}: cdaisy.C syntax.h common.h alist.h daisy.h parser_file.h \
 parser.h column.h librarian.h library.h weather.h im.h action.h \
 horizon.h printer_file.h printer.h
adsorbtion${OBJ}: adsorbtion.C adsorbtion.h librarian.h library.h common.h \
 alist.h syntax.h
tortuosity${OBJ}: tortuosity.C tortuosity.h librarian.h library.h common.h \
 alist.h syntax.h
event${OBJ}: event.C alist.h common.h event.h am.h library.h eventqueue.h \
 minimanager.h action.h column.h librarian.h syntax.h im.h daisy.h \
 weather.h crop.h
eventqueue${OBJ}: eventqueue.C common.h event.h alist.h am.h library.h \
 eventqueue.h daisy.h
minimanager${OBJ}: minimanager.C syntax.h common.h minimanager.h action.h \
 event.h alist.h am.h library.h eventqueue.h
printer${OBJ}: printer.C printer.h librarian.h library.h common.h alist.h \
 syntax.h
printer_file${OBJ}: printer_file.C printer_file.h printer.h librarian.h \
 library.h common.h alist.h syntax.h csmp.h options.h
set_exceptions${OBJ}: set_exceptions.S
main${OBJ}: main.C daisy.h common.h parser_file.h parser.h syntax.h \
 alist.h version.h
tkmain${OBJ}: tkmain.C daisy.h common.h syntax.h alist.h library.h
cmain${OBJ}: cmain.c cdaisy.h
