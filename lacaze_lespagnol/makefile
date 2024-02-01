CC = g++
CFLAGS = -std=c++17

SRC = main.cpp \
      Algo_PRIM/PrimL.cpp \
      Algo_PRIM/PrimM.cpp \
      Algo_PRIM/Sommet.cpp \
      Algo_PRIM/ArbreRecouvr.cpp

HEADER = Algo_PRIM/PrimL.h \
         Algo_PRIM/PrimM.h \
         Algo_PRIM/Sommet.h \
         Algo_PRIM/ArbreRecouvr.h

TARGET = lacaze_lespagnol

$(TARGET): $(SRC) $(HEADER)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

.PHONY: clean

clean:
	rm -f $(TARGET)