PHYS_SYS_OBJS = PhysicalSystemBase.o \
                Ising2D.o            \
				Heisenberg2D.o       \
				Heisenberg3D.o       \
				Elements.o           \
				CrystalBase.o        \
				CrystalStructure3D.o \
				Alloy3D.o

.PHONY : default owl-qe clean 

default : owl

owl : libPhysicalSystems.a

owl-qe :
	cd QuantumEspresso && $(MAKE) owl-qe

clean :
	rm -rf *.o *.a *.dSYM
	cd QuantumEspresso && $(MAKE) clean

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE_PATH) -c -o $@ $<

libPhysicalSystems.a : $(PHYS_SYS_OBJS)
	$(AR) -r $@ $(PHYS_SYS_OBJS)
	@echo " "
