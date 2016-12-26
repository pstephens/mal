#####################

DEBUG = 

TESTS =

OTHER_OBJS =

SOURCES_BASE = 
SOURCES_LISP = 
SOURCES = $(SOURCES_BASE) $(SOURCES_LISP)

#####################

SRCS = step0_repl.mal
ASMS = $(SRCS:%.mal=%.asm)
OBJS = $(ASMS:%.asm=%.o)
BINS = $(OBJS:%.o=%)

#####################

all: $(BINS)

dist: mal

mal: $(word $(words $(BINS)),$(BINS))
	cp $< $@

$(ASMS): %.asm: %.mal $(SOURCES)
	../fsharp/run $(@:%.asm=%.mal) > $@

$(OBJS): %.o: %.asm
	nasm -f elf64 -o $@ $(@:%.o=%.asm)

$(BINS): %: %.o
	ld -e _start -o $@ $(@:%=%.o)

clean:
	rm -f mal $(ASMS) $(OBJS) $(BINS) $(OTHER_OBJS)

.PHONY: stats tests $(TESTS)

stats: $(SOURCES)
	@wc $^
	@printf "%5s %5s %5s %s\n" `grep -E "^[[:space:]]*//|^[[:space:]]*$$" $^ | wc` "[comments/blanks]"
stats-lisp: $(SOURCES_LISP)
	@wc $^
	@printf "%5s %5s %5s %s\n" `grep -E "^[[:space:]]*//|^[[:space:]]*$$" $^ | wc` "[comments/blanks]"

tests: $(TESTS)

$(TESTS):
	@echo "Running $@"; \
	./$@ || exit 1; \
