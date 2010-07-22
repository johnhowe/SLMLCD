PROJECT_NAME = mmculib
RELEASE_NUM = 1.0.2
URL = https://svn.elec.canterbury.ac.nz/groups/mmicro

RELEASE_NAME = $(PROJECT_NAME)-$(RELEASE_NUM)
RELEASE_TAG = $(shell echo $(PROJECT_NAME)-$(RELEASE_NUM) | tr . _ | tr 'a-z' 'A-Z')


all:
	# Nothing to do

.PHONY: docs
docs: 
	(cd doc; doxygen doxygen.config)

.PHONY: release
release: docs
	svn copy -m "Generate release $(RELEASE_NAME)" $(URL)/trunk/$(PROJECT_NAME) $(URL)/tags/release/$(RELEASE_NAME)
	svn export  $(URL)/tags/release/$(RELEASE_NAME) $(RELEASE_NAME) 
	zip -r $(RELEASE_NAME).zip $(RELEASE_NAME)/*
	tar cvfhz $(RELEASE_NAME).tgz $(RELEASE_NAME)

clean:
	-rm *.bak *~ *.lst


