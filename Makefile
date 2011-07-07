# lighter
# created by raiden on 20110707
OBJS := chart.o lctrl.o light.o main.o

EXEC := a

#CFLAGS :=


all:$(EXEC)
$(EXEC):$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)
clean:
	rm -f $(OBJS) $(EXEC)
distclean:
	rm -f *.o $(EXEC)
