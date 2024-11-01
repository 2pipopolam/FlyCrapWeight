# Makefile generated by MakefileGenerator.cs
# *DO NOT EDIT*

UNREALROOTPATH = /home/pipopolam/Linux_Unreal_Engine_5.4.4
GAMEPROJECTFILE =/home/pipopolam/Documents/Unreal Projects/FlyweightDemo/FlyweightDemo.uproject

TARGETS = \
	FlyweightDemo-Linux-DebugGame  \
	FlyweightDemo-Linux-Shipping  \
	FlyweightDemo \
	FlyweightDemoEditor-Linux-DebugGame  \
	FlyweightDemoEditor-Linux-Shipping  \
	FlyweightDemoEditor \
	DotNetPerforceLib-Linux-DebugGame  \
	DotNetPerforceLib-Linux-Shipping  \
	DotNetPerforceLib \
	EventLoopUnitTests-Linux-DebugGame  \
	EventLoopUnitTests-Linux-Shipping  \
	EventLoopUnitTests \
	UnrealEditor-Linux-DebugGame  \
	UnrealEditor-Linux-Shipping  \
	UnrealEditor \
	UnrealGame-Linux-DebugGame  \
	UnrealGame-Linux-Shipping  \
	UnrealGame\
	configure

BUILD = bash "$(UNREALROOTPATH)/Engine/Build/BatchFiles/Linux/Build.sh"
PROJECTBUILD = "$(UNREALROOTPATH)/Engine/Binaries/ThirdParty/DotNet/6.0.302/linux/dotnet" "$(UNREALROOTPATH)/Engine/Binaries/DotNET/UnrealBuildTool/UnrealBuildTool.dll"

all: StandardSet

RequiredTools: CrashReportClient-Linux-Shipping CrashReportClientEditor-Linux-Shipping ShaderCompileWorker UnrealLightmass EpicWebHelper-Linux-Shipping

StandardSet: RequiredTools UnrealFrontend FlyweightDemoEditor UnrealInsights

DebugSet: RequiredTools UnrealFrontend-Linux-Debug FlyweightDemoEditor-Linux-Debug


FlyweightDemo-Linux-DebugGame:
	 $(PROJECTBUILD) FlyweightDemo Linux DebugGame  -project="$(GAMEPROJECTFILE)" $(ARGS)

FlyweightDemo-Linux-Shipping:
	 $(PROJECTBUILD) FlyweightDemo Linux Shipping  -project="$(GAMEPROJECTFILE)" $(ARGS)

FlyweightDemo:
	 $(PROJECTBUILD) FlyweightDemo Linux Development  -project="$(GAMEPROJECTFILE)" $(ARGS)

FlyweightDemoEditor-Linux-DebugGame:
	 $(PROJECTBUILD) FlyweightDemoEditor Linux DebugGame  -project="$(GAMEPROJECTFILE)" $(ARGS)

FlyweightDemoEditor-Linux-Shipping:
	 $(PROJECTBUILD) FlyweightDemoEditor Linux Shipping  -project="$(GAMEPROJECTFILE)" $(ARGS)

FlyweightDemoEditor:
	 $(PROJECTBUILD) FlyweightDemoEditor Linux Development  -project="$(GAMEPROJECTFILE)" $(ARGS)

DotNetPerforceLib-Linux-DebugGame:
	 $(BUILD) DotNetPerforceLib Linux DebugGame  -project="$(GAMEPROJECTFILE)" $(ARGS)

DotNetPerforceLib-Linux-Shipping:
	 $(BUILD) DotNetPerforceLib Linux Shipping  -project="$(GAMEPROJECTFILE)" $(ARGS)

DotNetPerforceLib:
	 $(BUILD) DotNetPerforceLib Linux Development  -project="$(GAMEPROJECTFILE)" $(ARGS)

EventLoopUnitTests-Linux-DebugGame:
	 $(BUILD) EventLoopUnitTests Linux DebugGame  -project="$(GAMEPROJECTFILE)" $(ARGS)

EventLoopUnitTests-Linux-Shipping:
	 $(BUILD) EventLoopUnitTests Linux Shipping  -project="$(GAMEPROJECTFILE)" $(ARGS)

EventLoopUnitTests:
	 $(BUILD) EventLoopUnitTests Linux Development  -project="$(GAMEPROJECTFILE)" $(ARGS)

UnrealEditor-Linux-DebugGame:
	 $(BUILD) UnrealEditor Linux DebugGame  -project="$(GAMEPROJECTFILE)" $(ARGS)

UnrealEditor-Linux-Shipping:
	 $(BUILD) UnrealEditor Linux Shipping  -project="$(GAMEPROJECTFILE)" $(ARGS)

UnrealEditor:
	 $(BUILD) UnrealEditor Linux Development  -project="$(GAMEPROJECTFILE)" $(ARGS)

UnrealGame-Linux-DebugGame:
	 $(BUILD) UnrealGame Linux DebugGame  -project="$(GAMEPROJECTFILE)" $(ARGS)

UnrealGame-Linux-Shipping:
	 $(BUILD) UnrealGame Linux Shipping  -project="$(GAMEPROJECTFILE)" $(ARGS)

UnrealGame:
	 $(BUILD) UnrealGame Linux Development  -project="$(GAMEPROJECTFILE)" $(ARGS)

configure:
	xbuild /property:Configuration=Development /verbosity:quiet /nologo "$(UNREALROOTPATH)/Engine/Source/Programs/UnrealBuildTool/UnrealBuildTool.csproj"
	$(PROJECTBUILD) -projectfiles -project="\"$(GAMEPROJECTFILE)\"" -game -engine 

.PHONY: $(TARGETS)
