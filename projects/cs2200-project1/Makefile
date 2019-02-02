# Authored by Christopher Tam for Georgia Tech's CS 2200
# Revised by Tanner Muldoon

CIRCUIT = *.sim
MICROCODE = microcode/*.mc
SUBMIT_FILES = $(CIRCUIT) $(MICROCODE)
SUBMISSION_NAME = project1-datapath

all: ;

submit:
	@(tar zcfh $(SUBMISSION_NAME).tar.gz $(SUBMIT_FILES) && \
	echo "Created submission archive $$(tput bold)$(SUBMISSION_NAME).tar.gz$$(tput sgr0).")
