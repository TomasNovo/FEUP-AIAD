JFLAGS = -g 
JC = javac
CLASSPATH = -classpath src
BIN = -d bin/
.SUFFIXES: .java .class
.java.class:
	$(JC) $(BIN) $(JFLAGS) $(CLASSPATH) $*.java

CLASSES = \
	src/logic/Macros.java \
	src/logic/Bid.java \
    src/logic/Client/Client.java \
    src/logic/CompilationFile.java \
    src/logic/CompiledProject.java \
    src/logic/CompiledProjectErrorType.java \
    src/logic/ExtendedAgent.java \
    src/logic/Pair.java \
    src/logic/ProjectInfo.java \
    src/logic/CPU/CPU.java \
    src/logic/CPU/Behaviours/NegotiationResponder.java \
    src/logic/Client/Behaviours/OfferProjectBehaviour.java \
    src/logic/Client/Behaviours/NegotiationInitiator.java 
 
default: classes
 
classes: $(CLASSES:.java=.class)
 
clean:
	$(RM) *.class