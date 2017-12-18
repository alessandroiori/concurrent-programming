 RM := rm -rf

all: HWC2LIST

HWC2LIST: $(OBJS) $(USER_OBJS)
	  gcc  -o"HWC2LIST" -lcunit *.c ./test/*.c

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) HWC2LIST
	-@echo ' '

