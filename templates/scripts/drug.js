// gets and displays information prompted by the search
async function loadJson() {
    
    // makes get request to the server to retrieve drug info json to be displayed
    const drugFile = await fetch("/api?" + new URLSearchParams({
        drugName: window.location.pathname.split("/").pop()
    }));

    const drugData = await drugFile.json(); // convert string to json object

    // display drug information in the side card
    document.getElementById("drugName").innerHTML = drugData.drugName;
    document.getElementById("subName").innerHTML = drugData.activeIngredients;

    var generics = "";
    for(i in drugData.generics){
        generics = generics + drugData.generics[i] + "<br>";
    }
    document.getElementById("generics").innerHTML = generics;

    var brandNames = "";
    for(i in drugData.brandNames){
        brandNames = brandNames + drugData.brandNames[i] + "<br>";
    }
    document.getElementById("brand-names").innerHTML = brandNames;

    // display interactions in dropdown menu
    var majorInter = "";
    for(i in drugData.interactions.major){
        majorInter = majorInter + '<li class="drug-bullet"><i class="bi bi-capsule"></i> ' + 
                        drugData.interactions.major[i] + '</li>';
    }
    document.getElementById("majordd").innerHTML = majorInter;

    var moderateInter = "";
    for(i in drugData.interactions.moderate){
        moderateInter = moderateInter + '<li class="drug-bullet"><i class="bi bi-capsule"></i> ' + 
                        drugData.interactions.moderate[i] + '</li>';
    }
    document.getElementById("moderatedd").innerHTML = moderateInter;

    var minorInter = "";
    for(i in drugData.interactions.minor){
        minorInter = minorInter + '<li class="drug-bullet"><i class="bi bi-capsule"></i> ' + 
                        drugData.interactions.minor[i] + '</li>';
    }
    document.getElementById("minordd").innerHTML = minorInter;

    var unknownInter = "";
    for(i in drugData.interactions.unknown){
        unknownInter = unknownInter + '<li class="drug-bullet"><i class="bi bi-capsule"></i> ' + 
                        drugData.interactions.unknown[i] + '</li>';
    }
    document.getElementById("unknowndd").innerHTML = unknownInter;
}

loadJson(); // calls function