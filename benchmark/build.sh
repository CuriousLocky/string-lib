#!/bin/bash

# Check if GRAAL_HOME is set
if [ -z "$GRAAL_HOME" ]; then
  echo "Error: GRAAL_HOME is not defined. Exiting."
  exit 1
fi

# If GRAAL_HOME is set, continue with the script
mvn verify

# recollect runtime trace
echo "Collecting trace..."
$GRAAL_HOME/bin/java -XX:+UnlockExperimentalVMOptions -XX:-UseJVMCICompiler -agentlib:native-image-agent=config-output-dir=graal-config -jar target/benchmarks.jar &> /dev/null

# Compile native image binary
$GRAAL_HOME/bin/native-image -H:ConfigurationFileDirectories=graal-config --initialize-at-build-time=org.openjdk.jmh.infra,org.openjdk.jmh.util.Utils,org.openjdk.jmh.runner.InfraControl,org.openjdk.jmh.runner.InfraControlL0,org.openjdk.jmh.runner.InfraControlL1,org.openjdk.jmh.runner.InfraControlL2,org.openjdk.jmh.runner.InfraControlL3,org.openjdk.jmh.runner.InfraControlL4 -jar target/benchmarks.jar -o ./target/benchmarks