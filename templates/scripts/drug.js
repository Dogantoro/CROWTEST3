
async function loadJson() {
    const drugFile = await fetch("/dev/json");
    const drugData = await drugFile.json();
    
    console.log(drugData);

}

loadJson();