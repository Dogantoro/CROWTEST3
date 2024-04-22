// gets and displays information prompted by the search
async function loadJson() {
    
    // makes get request to the server to retrieve drug info json to be displayed
    const drugFile = await fetch("/api?" + new URLSearchParams({
        drugName: window.location.pathname.split("/").pop()
    }));
    const drugData = await drugFile.json(); // convert string to json object

    // generate html code for drug info side card from json

    // insert side card content
    document.getElementById("drugName").innerHTML = drugData.drugName;

    // generate drug interaction code to return
    var majorInter = "";
    for(i in drugData.interactions.major){
        majorInter = majorInter + '<li class="drug-bullet"><i class="bi bi-capsule"></i> ' + 
                        drugData.interactions.major[i] + '</li>';
    }
    var moderateInter = "";
    for(i in drugData.interactions.moderate){
        moderateInter = moderateInter + '<li class="drug-bullet"><i class="bi bi-capsule"></i> ' + 
                        drugData.interactions.moderate[i] + '</li>';
    }
    var minorInter = "";
    for(i in drugData.interactions.minor){
        minorInter = minorInter + '<li class="drug-bullet"><i class="bi bi-capsule"></i> ' + 
                        drugData.interactions.minor[i] + '</li>';
    }
    var unknownInter = "";
    for(i in drugData.interactions.unknown){
        unknownInter = unknownInter + '<li class="drug-bullet"><i class="bi bi-capsule"></i> ' + 
                        drugData.interactions.unknown[i] + '</li>';
    }

    // insert drug interaction drop down contents
    document.getElementById("majordd").innerHTML = majorInter;
    document.getElementById("moderatedd").innerHTML = moderateInter;
    document.getElementById("minordd").innerHTML = minorInter;
    document.getElementById("unknowndd").innerHTML = unknownInter;

    var numberHead = `<span class="badge text-bg-danger">`;

    document.getElementById("major-title").insertAdjacentHTML("beforebegin", numberHead + drugData.interactions.major.length + "</span>");
    document.getElementById("moderate-title").insertAdjacentHTML("beforebegin", numberHead + drugData.interactions.moderate.length + "</span>");
    document.getElementById("minor-title").insertAdjacentHTML("beforebegin", numberHead + drugData.interactions.minor.length + "</span>");
    document.getElementById("unknown-title").insertAdjacentHTML("beforebegin", numberHead + drugData.interactions.unknown.length + "</span>");
}

loadJson(); // calls function