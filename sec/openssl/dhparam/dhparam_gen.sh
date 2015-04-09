#!/bin/sh

# Check usage
if [ ${#} -ne 2 ]; then
	echo "Usage: ${0} <generator> <bits>"
	exit 1
fi

# Assign parameters
GENERATOR=${1}
BITS=${2}

# Validate parameters
if [ ${GENERATOR} -ne 2 ]; then
	if [ ${GENERATOR} -ne 5 ]; then
		echo "Invalid generator (only the values 2 and 5 are acceptable)."
		exit 1
	fi
fi

# Create destination directory
mkdir -p ${GENERATOR}/${BITS}
if [ ${?} -ne 0 ]; then
	echo "Failed to create destination directory."
	exit 1
fi

# Generate dhparams
openssl dhparam -${GENERATOR} -out dhparam-${GENERATOR}-${BITS}.pem ${BITS}
if [ ${?} -ne 0 ]; then
	echo "Unable to generate dhparam."
	exit 1
fi

# Check dhparams
openssl dhparam -check -in dhparam-${GENERATOR}-${BITS}.pem
if [ ${?} -ne 0 ]; then
	echo "The generated dhparams are invalid."
	exit 1
fi

# Convert to text
openssl dhparam -in dhparam-${GENERATOR}-${BITS}.pem -text -noout > ${GENERATOR}/${BITS}/dhparam-${GENERATOR}-${BITS}.txt
if [ ${?} -ne 0 ]; then
	echo "Unable to convert dhparam to text."
	exit 1
fi

# Convert to C code
openssl dhparam -in dhparam-${GENERATOR}-${BITS}.pem -C -noout > ${GENERATOR}/${BITS}/dhparam-${GENERATOR}-${BITS}.c
if [ ${?} -ne 0 ]; then
	echo "Unable to convert dhparam to C."
	exit 1
fi

# Convert to DER
openssl dhparam -inform PEM -outform DER -in dhparam-${GENERATOR}-${BITS}.pem -out ${GENERATOR}/${BITS}/dhparam-${GENERATOR}-${BITS}.der
if [ ${?} -ne 0 ]; then
	echo "Unable to convert dhparam (PEM -> DER)."
	exit 1
fi

# Move the PEM
mv dhparam-${GENERATOR}-${BITS}.pem ${GENERATOR}/${BITS}/dhparam-${GENERATOR}-${BITS}.pem
if [ ${?} -ne 0 ]; then
	echo "Unable to copy dhparam (PEM) to destination directory."
	exit 1
fi

echo "Done."

