# This file is generated by gyp; do not edit.

TOOLSET := target
TARGET := oracle_client
DEFS_Debug := \
	'-D_LARGEFILE_SOURCE' \
	'-D_FILE_OFFSET_BITS=64' \
	'-DBUILDING_NODE_EXTENSION' \
	'-DDEBUG' \
	'-D_DEBUG'

# Flags passed to all source files.
CFLAGS_Debug := \
	-fPIC \
	-Wall \
	-Wextra \
	-Wno-unused-parameter \
	-pthread \
	-m64 \
	-fexceptions \
	-g \
	-O0

# Flags passed to only C files.
CFLAGS_C_Debug :=

# Flags passed to only C++ files.
CFLAGS_CC_Debug := \
	-fno-rtti \
	-fno-exceptions \
	-fexceptions

INCS_Debug := \
	-I/home/zhs/.node-gyp/0.10.22/src \
	-I/home/zhs/.node-gyp/0.10.22/deps/uv/include \
	-I/home/zhs/.node-gyp/0.10.22/deps/v8/include \
	-I$(srcdir)/../oci \
	-I$(srcdir)/../un/include

DEFS_Release := \
	'-D_LARGEFILE_SOURCE' \
	'-D_FILE_OFFSET_BITS=64' \
	'-DBUILDING_NODE_EXTENSION'

# Flags passed to all source files.
CFLAGS_Release := \
	-fPIC \
	-Wall \
	-Wextra \
	-Wno-unused-parameter \
	-pthread \
	-m64 \
	-fexceptions \
	-O2 \
	-fno-strict-aliasing \
	-fno-tree-vrp \
	-fno-tree-sink

# Flags passed to only C files.
CFLAGS_C_Release :=

# Flags passed to only C++ files.
CFLAGS_CC_Release := \
	-fno-rtti \
	-fno-exceptions \
	-fexceptions

INCS_Release := \
	-I/home/zhs/.node-gyp/0.10.22/src \
	-I/home/zhs/.node-gyp/0.10.22/deps/uv/include \
	-I/home/zhs/.node-gyp/0.10.22/deps/v8/include \
	-I$(srcdir)/../oci \
	-I$(srcdir)/../un/include

OBJS := \
	$(obj).target/$(TARGET)/src/oracle_client.o \
	$(obj).target/$(TARGET)/src/Connection.o \
	$(obj).target/$(TARGET)/../third_party/CodingConv/encodeutil.o \
	$(obj).target/$(TARGET)/../core/plateform_public.o \
	$(obj).target/$(TARGET)/src/nodefunction.o \
	$(obj).target/$(TARGET)/../core/otlPool.o \
	$(obj).target/$(TARGET)/src/ConnctionPool.o \
	$(obj).target/$(TARGET)/../un/src/linux/thread.o

# Add to the list of files we specially track dependencies for.
all_deps += $(OBJS)

# CFLAGS et al overrides must be target-local.
# See "Target-specific Variable Values" in the GNU Make manual.
$(OBJS): TOOLSET := $(TOOLSET)
$(OBJS): GYP_CFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_C_$(BUILDTYPE))
$(OBJS): GYP_CXXFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_CC_$(BUILDTYPE))

# Suffix rules, putting all outputs into $(obj).

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(srcdir)/%.cc FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(srcdir)/%.c FORCE_DO_CMD
	@$(call do_cmd,cc,1)

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(srcdir)/%.cpp FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

# Try building from generated source, too.

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj).$(TOOLSET)/%.cc FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj).$(TOOLSET)/%.c FORCE_DO_CMD
	@$(call do_cmd,cc,1)

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj).$(TOOLSET)/%.cpp FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj)/%.cc FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj)/%.c FORCE_DO_CMD
	@$(call do_cmd,cc,1)

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj)/%.cpp FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

# End of this set of suffix rules
### Rules for final target.
LDFLAGS_Debug := \
	-pthread \
	-rdynamic \
	-m64

LDFLAGS_Release := \
	-pthread \
	-rdynamic \
	-m64

LIBS := \
	-lclntsh \
	-lpthread \
	-L /home/zhs/oracle/product/10.2.0/db_2/lib/

$(obj).target/oracle_client.node: GYP_LDFLAGS := $(LDFLAGS_$(BUILDTYPE))
$(obj).target/oracle_client.node: LIBS := $(LIBS)
$(obj).target/oracle_client.node: TOOLSET := $(TOOLSET)
$(obj).target/oracle_client.node: $(OBJS) FORCE_DO_CMD
	$(call do_cmd,solink_module)

all_deps += $(obj).target/oracle_client.node
# Add target alias
.PHONY: oracle_client
oracle_client: $(builddir)/oracle_client.node

# Copy this to the executable output path.
$(builddir)/oracle_client.node: TOOLSET := $(TOOLSET)
$(builddir)/oracle_client.node: $(obj).target/oracle_client.node FORCE_DO_CMD
	$(call do_cmd,copy)

all_deps += $(builddir)/oracle_client.node
# Short alias for building this executable.
.PHONY: oracle_client.node
oracle_client.node: $(obj).target/oracle_client.node $(builddir)/oracle_client.node

# Add executable to "all" target.
.PHONY: all
all: $(builddir)/oracle_client.node
