ROOTLIBS   = $(shell root-config --libs)
ROOTCFLAGS = $(shell root-config --cflags)

CFLAG      = -I $(ROOTCFLAGS)
LFLAG      = $(ROOTLIBS)

OBJ     = Config.o DataSet.o Event.o EventBuilder.o EventInfoPrinter.o GlobalParameters.o MrRA2.o PlotBuilder.o Selection.o Variable.o


run: $(OBJ)		
	g++ $(OBJ) $(LFLAG) -o run
	@echo -e 'Done.\n\n   Type "./run" and let Mr RA2 search for SUSY.\n\n'

Config.o: Config.h Config.cc
	g++ $(CFLAG) -c  Config.cc

DataSet.o: DataSet.h DataSet.cc Config.h Event.h Variable.h
	g++ $(CFLAG) -c  DataSet.cc

Event.o: Event.h Event.cc
	g++ $(CFLAG) -c  Event.cc

EventBuilder.o: EventBuilder.h EventBuilder.cc Event.h Variable.h
	g++ $(CFLAG) -c  EventBuilder.cc

EventInfoPrinter.o: EventInfoPrinter.h EventInfoPrinter.cc Config.h DataSet.h Event.h Variable.h
	g++ $(CFLAG) -c  EventInfoPrinter.cc

GlobalParameters.o: GlobalParameters.h GlobalParameters.cc Config.h
	g++ $(CFLAG) -c  GlobalParameters.cc

MrRA2.o: MrRA2.h MrRA2.cc DataSet.h Config.h GlobalParameters.h PlotBuilder.h Selection.h Variable.h
	g++ $(CFLAG) -c  MrRA2.cc

PlotBuilder.o: PlotBuilder.h PlotBuilder.cc DataSet.h Variable.h Config.h GlobalParameters.h Event.h ../AdditionalInputFiles/RA2PlottingStyle.h
	g++ $(CFLAG) -c  PlotBuilder.cc

Selection.o: Selection.h Selection.cc Config.h DataSet.h Event.h
	g++ $(CFLAG) -c  Selection.cc

Variable.o: Variable.h Variable.cc Config.h
	g++ $(CFLAG) -c  Variable.cc



clean:
	@rm -f *.o 
	@rm -f run
	@rm -f *~
	@rm -f *#
	@rm -f .#*


