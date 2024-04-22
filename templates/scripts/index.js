// code for the improper search alert -----------------------------------------

let searchAlert = `
<div class="home-card alert alert-dark alert-dismissible fade show col-10 m-auto mt-3" role="alert">
      <i class="bi bi-exclamation-circle-fill me-1"></i>
      <strong>Search not Found</strong> - check your input and try again!
      <button type="button" class="btn-close" data-bs-dismiss="alert" aria-label="Close"></button>
</div>
`;

function addAlert() {
    const elem = document.getElementById("homeCard");
    elem.insertAdjacentHTML("afterend", searchAlert);
}

if (window.location.search == "?error") {
    addAlert();
}

// code to save the selected datastructre for searching -----------------------

function adjList() {
    document.cookie = "dataStruct=list";
    location.reload();
}

function adjMatrix() {
    document.cookie = "dataStruct=matrix";
    location.reload();
}

var listRadio = document.getElementById('AdjListRadio');
var matrixRadio = document.getElementById('AdjMatrixRadio');

listRadio.onclick = adjList;
matrixRadio.onclick = adjMatrix;


if (document.cookie.indexOf('dataStruct=') == -1) {
    document.cookie = "dataStruct=list";
}

if(document.cookie == "dataStruct=matrix") {
    matrixRadio.checked = true;
}
else {
    listRadio.checked = true;
}

console.log(document.cookie);

