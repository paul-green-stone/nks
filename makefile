cc := gcc

OBJDIR := objects
CFLAGS := -g -O1 -fpic

LDFLAGS := -lSDL2 -lSDL2_image -lm

$(OBJDIR)/main.o: main.c $(OBJDIR)/rules.o ps-sdl-wrapper/libps.a
	$(cc) $(CFLAGS) -o a.out $^ $(LDFLAGS)

ps-sdl-wrapper/libps.a:
	$(MAKE) -C ps-sdl-wrapper

$(OBJDIR)/rules.o: src/rules.c
	$(cc) -c $(CFLAGS) -o $@ $^

# ================================================================ #

.PHONY: clean

clean:
	rm -rf $(OBJDIR) ./*.a ./*.o ./*.out

# ================================ #

$(shell mkdir -p $(OBJDIR))