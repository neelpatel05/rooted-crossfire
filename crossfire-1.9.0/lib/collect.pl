#!/usr/bin/perl

require "util.pl";

if ($#ARGV >= 0) {
    if ($ARGV[0] =~ m/^--?[hH](elp)?$/) {
	die ("\nUSAGE: perl collect.pl  ARCHDIR\n".
	     "\nWhere ARCHDIR is the directory where you stored the ".
	     "raw archetypes.\n".
	     "This script will then create these files:\n".
	     "archetypes,bmaps,bmaps.paths,faces,treasures.bld,animations.\n"
	)
    }
}

# archonly is used to only build the archetypes.  I find this
# very handy if I know I've only changed .arc files - I don't want
# to rebuild the other files, because now cvs tries to do diffs
# on them as well as commit them, even if there are no changes.
$archonly = 0;
if ($#ARGV >= 1) {
    if ($ARGV[1] eq "ARCHONLY") { $archonly = 1; }
    else {print "Ignoring unknown option: $ARGV[1]\n"; }
}


$root = $ARGV[0];
$archetypes = "archetypes";
$bmaps = "bmaps";
$faces = "faces";
$treasures = "treasures.bld";
$animations = "animations";
$paths = $bmaps."."."paths";
$faceExt = "\\.[a-zA-Z0-9][A-Z0-9][A-Z0-9]";
$smooths = "smooth";

### main
&info("looking ...");
&traverse($root);

$attacktype{ 'physical' } = ( 1 << 0 );
$attacktype{ 'magic' } = ( 1 << 1 );
$attacktype{ 'fire' } = ( 1 << 2 );
$attacktype{ 'electricity' } = ( 1 << 3 );
$attacktype{ 'cold' } = ( 1 << 4 );
$attacktype{ 'confusion' } = ( 1 << 5 );
$attacktype{ 'acid' } = ( 1 << 6 );
$attacktype{ 'drain' } = ( 1 << 7 );
$attacktype{ 'weaponmagic' } = ( 1 << 8 );
$attacktype{ 'ghosthit' } = ( 1 << 9 );
$attacktype{ 'poison' } = ( 1 << 10 );
$attacktype{ 'slow' } = ( 1 << 11 );
$attacktype{ 'paralyze' } = ( 1 << 12 );
$attacktype{ 'turnundead' } = ( 1 << 13 );
$attacktype{ 'fear' } = ( 1 << 14 );
$attacktype{ 'cancellation' } = ( 1 << 15 );
$attacktype{ 'deplete' } = ( 1 << 16 );
$attacktype{ 'death' } = ( 1 << 17 );
$attacktype{ 'chaos' } = ( 1 << 18 );
$attacktype{ 'counterspell' } = ( 1 << 19 );
$attacktype{ 'godpower' } = ( 1 << 20 );
$attacktype{ 'holyword' } = ( 1 << 21 );
$attacktype{ 'blind' } = ( 1 << 22 );
$attacktype{ 'internal' } = ( 1 << 23 );
$attacktype{ 'lifestealing' } = ( 1 << 24 );
$attacktype{ 'disease' } = ( 1 << 25 );

&info("writing ...$archetypes");
open(ARCH,">".$archetypes) || &die("cannot open ".$archetypes);
&archsOut($root);
close(ARCH);


if (!$archonly) {
    &info("$bmaps");
    open(BMAPS,">".$bmaps) || &die("cannot open ".$bmaps);
    &bmapsOut;
    close(BMAPS);

    open(BMAPS,">".$paths) || &die("cannot open ".$paths);
    &pathsOut;
    close(BMAPS);

    &info("$faces");
    open(FACES,">".$faces) || &die("cannot open ".$faces);
    &facesOut;
    close(FACES);

    &info("$smooths");
    open(SMOOTHS,">".$smooths) || &die("cannot open ".$smooths);
    &smoothOut;
    close(SMOOTHS);

    &info("$treasures");
    # We still support the old consolidated treasure information
    # so copy it over.
    open(TREASURES,">".$treasures) || &die("cannot open ".$treasures);
    print TREASURES "#
# Do not modify this file - any changes will get overwritten.
# instead, modify the treasures file or the .trs file in the
# arch directory.\n#
";

    open(TR, "<treasures");
    while (<TR>) {
	print TREASURES $_;
    }
    close(TR);
    print TREASURES "#\n# Start of collected .trs files\n#\n";

    &treasuresOut;
    close(TREASURES);

    &info("$animations");
    open(ANIM,">".$animations) || &die("cannot open ".$animations);
    &animOut;
    close(ANIM);
}


&stats;
exit 0;

sub traverse {
    local($dir) = shift;
    local($file,$name);
    local( $tfile);

    opendir(THISDIR, $dir) || die "couldn't open $dir";
    local(@allfiles) = readdir(THISDIR);
    closedir(THISDIR);

    foreach $tfile (sort @allfiles) {
	next if $tfile =~ /^\./;
	$file = $dir."/".$tfile;
	$name = &basename($file,""); # DIR

	if( -d $file && $name ne "dev" && $name ne "trashbin" && $name ne "CVS" ) {
	    &traverse($file);
	} elsif ( -d $file && ( $name eq "dev" || $name eq "trashbin" ) ) {
# Empty directive to prevent warnings below
	} elsif( $file =~ /.*\.arc$/) {	# ARCHETYPE
	    $archsNum++;
	    push(@archs,$file);n
	} elsif( $name =~ /(\S+)\.base($faceExt)\.png$/) { # FACE
	    $facesNum++;
	    $im_name = "$1$2";
	    &warn("duplicate face $im_name in ".$dir." and $faces{$im_name}")
		if $faces{$im_name};
	    $faces{$im_name} = $dir."/".$im_name;

	} elsif ( $file =~ /.*\.face$/) {	# Face information file
	    $facesFileNum++;
	    push(@face_files, $file);
	} elsif ( $file =~ /.*\.trs$/) {	# Treasure information file
	    push(@treasure_files, $file);
	} 
	elsif ( $file =~ /\.png$/ || $file =~ /\.xpm$/ || $file =~ /$faceExt$/) {
	# we cover many files we probably shouldn't, but oh well.
	# we just don't want complaints about all of these.
	}
	# ignore a couple of the more common 'junk' files that are not
	# really junk.
	elsif (($name ne "README") && ($name ne "CVS")) {
	    $trashNum++;
	    print "Warning: $file might be a junk file\n";
	}
    }
}

sub storeFaceInfo {
    local($lface,@values) = @_;

    if ($values[0] ne "") {
#	blank.111 is a special case -
#	since no foreground pixels will actually be drawn, foreground colors is
#	not relevant.  Several monsters use blank.111 as part of their
#	animation to make them appear invisible, but have some other
#	foreground color set.
#	Same applies to empty also.
	if ($fg{$lface} && $fg{$lface} ne $values[0] && $lface ne "blank.111"
		&& $lface ne "empty.111") {
	    &warn($arch." duplicate fg color ".$fg{$lface}."/".$values[0]." face ".$lface);
	} else {
	    $fg{$lface} = $values[0];
	}
    }
    if ($values[1] ne "") {
	if ($bg{$lface} && $bg{$lface} ne $values[1]) {
	    &warn($arch." duplicate bg color ".$bg{$lface}."/".$values[1]." face ".$lface);
	} else {
	    $bg{$lface} = $values[1];
	}
    }
    if ($values[2] ne "" && $lface ne "blank.111" && $lface ne "empty.111") {
#      blank.111 is a special case - see above explanation
#      Its visibility is always 0.
	if ($visibility{$lface} && $visibility{$lface} ne $values[2]) {
	    &warn($arch." duplicate visibilty ".$visibility{$lface}."/".$values[2]." face ".$lface);
	} else {
	    $visibility{$lface} = $values[2];
	}
    }
    if ($values[3] ne "" && lface ne "blank.111" && $lface ne "empty.111") {
	if ($magicmap{$lface} && $magicmap{$lface} ne $values[3]) {
	    &warn($arch." duplicate magicmap color ".$magicmap{$lface}."/".$values[3]." face ".$lface);
	} else {
	    $magicmap{$lface} = $values[3];
	}
    }
    if ($values[4] ne "") {
	if ($floor{$lface} && $floor{$lface} ne $values[4]) {
	    &warn($arch." duplicate floor information ".$floor{$lface}."/".$values[4]." face ".$lface);
	} else {
	    $floor{$lface} = $values[4];
	}
    }
}


sub archsOut {
    local($dir) = shift;

    foreach $arch (@archs) {
	# Assume the filename $arch begins with $dir. Assign the first path
	# name component after $dir to $pathto.
	if($arch =~ /^\Q$dir\E\/([^\/]+)\/.*[.]arc$/) {
	    $pathto = $1;
	} else {
	    &warn("cannot determine editor_folder from arch '$arch'");
	    $pathto = "";
	}
	open(ARC,$arch) || &die("cannot open ".$arch);
line:	while(<ARC>) {
	    chop;
	    ($var,@values) = split;
	    if ($var eq "#") {
		#developper comment, switch to next line
		$commentNum++;
		next line;
	    }
	    if ($var eq "Object") {
		$lface[0] = "";
		$#lface = 0;
		$lfg = "";
		$lbg = "";
		$lvis = "";
		$mm = "";
		$floor = "";
		$walkon = 0;
		$nopick = 0;
		$arch = join "_", @values;
	    }
	    if ($var eq "end") {
		if ($#lface !=0) {
		    $#lface--;
		    foreach $face (@lface) {
			&storeFaceInfo($face, $lfg, $lbg, $lvis,$mm,$floor);
		    }
	 	}
		if ($walkon && !$nopick) {
		    &warn("File $arch has an object with walk_on set which can be picked up\n");
		}
	    }
	    # Process the color/face info now
	    if ($var eq "color_fg") {
		$lfg = $values[0];
		next line;
	    }
	    if ($var eq "color_bg") {
		$lbg = $values[0];
		next line;
	    }
	    if ($var eq "end") {
		print ARCH "editor_folder $pathto\n" if $pathto ne "";
	    }
	    if ($var eq "visibility") {
		$lvis = $values[0];
		next line;
	    }
	    if ($var eq "magicmap") {
		$mm = $values[0];
		next line;
	    }
	    if ($var eq "attacktype") {
		$at = 0;
		foreach $t ( @values ) {
		    if ( $t =~ /^\d+$/ ) {
			$at |= $t;
		    } else {
			if ( defined( $attacktype{ $t } ) ) {
			    $at |= $attacktype{ $t };
			} else {
			    &warn($arch . " has invalid attacktype " . $t);
			}
		    }
		}
		$_ = $var . ' ' . $at;
	    }
	    if ($var eq "is_floor") {
		$floor = $values[0];
		# is_floor is also needed for archs, so let it pass
		# through
	    }
	    elsif ($var eq "no_pick") {
		$nopick = $values[0];
	    } elsif ($var eq "walk_on") {
		$walkon = $values[0];
	    }
	    elsif ($var eq "face") {
		$lface[$#lface++] = $values[0]
	    }
	    elsif ($var eq "anim") {
		if ($anim{$arch}) {
		    &warn("$arch is a duplicate animation name");
		    $anim{$arch}="";
		}
		while (<ARC>) {
		    chomp;
		    $var = $_;
		    last if ($var =~ "mina\s*");
		    if ($var =~ /facings \S+$/) { }
		    elsif (! $faces{$var}) {
			&warn($arch." is missing face ".$var);
		    }
		    else {
			$lface[$#lface++] = $var;
		    }
		    $anim{$arch} .= "$var\n";
		}
		print ARCH "animation $arch\n";
		next line;	# don't want the mina
	    }
	    if ($var eq "face" && ! $faces{$values[0]}) {
		&warn($arch." is missing face ".$values[0])
	    }
	    if ($var eq "smoothface") {
		if ($smoothing{$values[0]} && ($smoothing{$values[0]} ne $values[1])) {
		    &warn($arch." duplicate smoothface for ".$values[0].": ".$smoothing{$values[0]}." and ".$values[1]);
		} elsif ( ($values[0] eq "") || ($values[1] eq "")) {
		    &warn ($arch." incomplete smoothface entry found: ".$values[0]." ".$values[1]);
		} else {
		    $smoothing{$values[0]}=$values[1]
		}
		next line;  #smoothface must be excluded from archetype file
	    }
	    print ARCH $_,"\n";
	}
	close(ARC);
    }
}

sub pline {
    local($face) = shift;
    print BMAPS sprintf("%05d",$idx++)," ",$face,"\n";
}

sub opline {
    local($face) = shift;
    print BMAPS sprintf("\\%05d",$idx++),"\t",$face,"\n";
}

sub pheader {
    print BMAPS "# This file is generated by $0, do not edit\n";
}

sub bmapsOut {
    &pheader;
    $idx = 0;
    &pline("bug.111");
    foreach $face (sort(keys %faces)) {
	&pline($face) if $face !~ /bug\.111/;
    }
}

sub pathsOut {
    &pheader;
    $idx = 0;
    &opline($root."/system/bug.111");
    foreach $face (sort(keys %faces)) {
	&opline($faces{$face}) if $faces{$face} !~ /bug\.111/;
    }
}

sub treasuresOut {
    foreach $treasure (@treasure_files) {
	open(TREAS, $treasure) || &die("cannot open ".$treasure);
	while(<TREAS>) {
	    if (! /^\s*$/) {
		print TREASURES $_;
	    }
	}
	close(FACE);
    }
}

sub facesOut {
    foreach $face (@face_files) {
	open(FACE, $face) || &die("cannot open ".$face);
	while(<FACE>) {
	    chop;
	    local ($var, @values) = split;
	    if ($var eq "face") {
		$lface = $values[0];
		$lfg = "";
		$lbg = "";
		$lvis = "";
		$mm = "";
		$floor = "";
	    }
	    elsif ($var eq "color_fg") {
		$lfg = $values[0];
	    }
	    elsif ($var eq "color_bg") {
		$lbg = $values[0];
	    }
	    elsif ($var eq "visibility") {
		$lvis = $values[0];
	    }
	    elsif ($var eq "magicmap") {
		$mm = $values[0];
	    }
	    elsif ($var eq "is_floor") {
		$floor = $values[0];
	    }
	    elsif ($var eq "end") {
		&storeFaceInfo($lface, $lfg, $lbg, $lvis, $mm, $floor);
	    }
	    elsif ($var eq "animation") {
		$animation=$values[0];
		if ($anim{$1}) {
		    &warn("$animation is a duplicate animation name");
		    $anim{$animation}="";
		}
		while (<FACE>) {
		    chomp;
		    $var = $_;
		    last if ($var =~ /^mina\s*$/);
		    if ($var !~ /^facings/ ) {
		    	if (! $faces{$var}) {
			    &warn($arch." is missing face ".$var);
			}
			else {
			    $lface[$#lface++] = $var;
			}
		    }
		    $anim{$animation} .= "$var\n";
		}
		next;	# don't want the mina
	    }
	}
	close(FACE);
    }
    print FACES "# This file is generated by $0, do not edit\n";
    foreach $face (sort(keys %faces)) {
	if ($fg{$face} ne "" || $bg{$face} ne "" || $visibility{$face} ne "" ||
	    $magicmap{$face} ne "" || $floor{$face} ne "") {
	    print FACES "face ".$face."\n";
	    print FACES "color_fg ".$fg{$face}."\n"
	    if $fg{$face} ne "";
		print FACES "color_bg ".$bg{$face}."\n"
	    if $bg{$face} ne "";
		print FACES "visibility ".$visibility{$face}."\n"
	    if $visibility{$face} ne "";
		print FACES "magicmap ".$magicmap{$face}."\n"
	    if $magicmap{$face} ne "";
		print FACES "is_floor ".$floor{$face}."\n"
	    if $floor{$face} ne "";
		print FACES "end\n";
	}
    }
}

sub animOut {
    foreach $anim (sort keys %anim) {
	print ANIM "anim $anim\n$anim{$anim}mina\n";
	$animationsNum++;
    }
}
sub smoothOut {
    local ($sm);
    print SMOOTHS "##########################################################\n";
    print SMOOTHS "# Do not touch this file.                                #\n";
    print SMOOTHS "# It has been generated from the informations present    #\n";
    print SMOOTHS "# in the archetype files.                                #\n";
    print SMOOTHS "# To add new entries, simply add                         #\n";
    print SMOOTHS "#     smoothface xxx yyy                                 #\n";
    print SMOOTHS "# to an archetype and collect.pl will put below an entry #\n";
    print SMOOTHS "#      xxx yyy                                           #\n";
    print SMOOTHS "##########################################################\n\n";
    print SMOOTHS "# default smooth. Needed for fallbacking\n";
    print SMOOTHS "default_smoothed.111 sdefault.001\n";
    print SMOOTHS "\n# Data extracted from arch files\n";
    foreach $sm (sort (keys %smoothing)) {
	print SMOOTHS "$sm $smoothing{$sm}\n";
	$smoothNum++;
    }
}

### print out statical information
sub stats {
    &info(Archs.":\t".$archsNum);
    &info(Images.":\t".$facesNum);
    &info(Faces.":\t".$facesFileNum);
    &info(Animations.":\t".$animationsNum);
    &info(Treasures.":\t".($#treasure_files+1));
    &info(Trash.":\t".$trashNum);
    &info(Smooths.":\t".$smoothNum);
    &info("Comment lines:\t".$commentNum);
}
