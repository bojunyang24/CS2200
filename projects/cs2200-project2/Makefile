# Authored by Christopher Tam for Georgia Tech's CS 2200
# Revised by Tanner Muldoon

CIRCUIT = *.sim
MICROCODE = microcode/*.mc
ASSEMBLY = assembly/*.s
SUBMIT_FILES = $(CIRCUIT) $(MICROCODE) $(ASSEMBLY)
SUBMISSION_NAME = project2-interrupts

all: ;

submit:
	@(tar zcfh $(SUBMISSION_NAME).tar.gz $(SUBMIT_FILES) && \
	echo "Created submission archive $$(tput bold)$(SUBMISSION_NAME).tar.gz$$(tput sgr0).")
