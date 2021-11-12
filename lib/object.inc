# Basic library for objects
. lib/common.inc

serialize(){
	[ -z "$_ID" ] && return 1
	env | grep -E "^_.+=" | sed 's/^_/export _/g' > $OBJECTS/$_ID
	return $?
}

deserialize(){
	ID=$1
	[ -z "$ID" ] \
		&& echo "No ID provided." >&2 \
		&& return 1
	if [ ! -z "$ID" -a -f $OBJECTS/$ID ]; then
		. $OBJECTS/$ID
	else
		echo "$ID is not a valid ID." >&2
	        return 2
	fi
	[ -z "$_CLASS" ] && _CLASS=dummy
	if [ -f $CLASSES/$_CLASS ]; then
		. $CLASSES/$_CLASS
	else
		echo "$_CLASS is not a valid CLASS for $_ID" >&2
		return 3
	fi
	return 0
}

_get(){
	ATTRIBUTE="_$(echo $1|tr [:lower:] [:upper:])"
	eval echo \$$ATTRIBUTE
}

_set(){
	ATTRIBUTE="_$(echo $1|tr [:lower:] [:upper:])"
	shift
	eval export $ATTRIBUTE=\"$*\"
	serialize
}

