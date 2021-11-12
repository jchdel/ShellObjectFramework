# Basic library for objects
. lib/common.inc

serialize(){
	[ -z "$_ID" ] && return 1
	env | grep -E "^_.+=" | sed 's/^_/export _/g' > $OBJECTS/$_ID
	return $?
}

deserialize(){
	_ID=$1
	[ -z "$_ID" ] \
		&& echo "No ID provided." >&2 \
		&& return 1
	if [ ! -z "$_ID" -a -f $OBJECTS/$_ID ]; then
		. $OBJECTS/$_ID
	else
		echo "$_ID is not a valid ID." >&2
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

