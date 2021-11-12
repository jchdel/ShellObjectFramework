#OBJECTS=/var/local/lib/objects
#CLASSES=/usr/local/lib/classes
OBJECTS=local/lib/objects
CLASSES=lib/classes
[ ! -d $CLASSES ] \
	&& echo "No classes directory found." >&2 \
	&& exit 1
mkdir -p $OBJECTS
for i in $(ls $CLASSES/* -d);do
	mkdir -p "$OBJECTS/../classes/$(basename $i)"
done

die(){
	cd $PWD
	exit $1
}

