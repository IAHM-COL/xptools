PLATFORM	:= $(shell uname)

ifneq (, $(findstring MINGW, $(PLATFORM)))
TARGETS :=	WED MeshTool ObjView DSFTool DDSTool ObjConverter \
		ac3d XGrinder
else
TARGETS :=	WED MeshTool ObjView DSFTool DDSTool ObjConverter RenderFarm \
		ac3d XGrinder RenderFarmUI
endif

.PHONY: $(TARGETS) all clean distclean release linkclean release-test \
srpm-head

all: $(TARGETS)

debug:
	@$(MAKE) -s -C . conf=debug all

debug-opt:
	@$(MAKE) -s -C . conf=debug_opt all

release:
	@$(MAKE) -s -C . conf=release all

release-opt:
	@$(MAKE) -s -C . conf=release_opt all

release-test:
	@$(MAKE) -s -C . conf=release_test all

clean:
	@$(MAKE) -s -f ./makerules/global/toplevel.mk clean

linkclean:
	@$(MAKE) -s -f ./makerules/global/toplevel.mk TARGET=$(target) linkclean

srpm-head:
	git archive --format=tar --prefix=xptools/ HEAD^{tree} | bzip2 > xptools.tar.bz2
	rpmbuild -ts xptools.tar.bz2
	rm -rf xptools.tar.bz2

ifndef rpmbuild
$(TARGETS):
else
$(TARGETS):
endif
	@export LD_RUN_PATH='$${ORIGIN}/slib' && \
	$(MAKE) -s -f ./makerules/global/toplevel.mk TARGET=$(@) all

