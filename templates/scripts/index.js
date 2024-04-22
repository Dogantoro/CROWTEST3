let searchAlert = `
<div class="home-card alert alert-dark alert-dismissible fade show col-10 m-auto mt-3" role="alert">
      <i class="bi bi-exclamation-circle-fill me-1"></i>
      <strong>Search not Found</strong> - check your input and try again!
      <button type="button" class="btn-close" data-bs-dismiss="alert" aria-label="Close"></button>
</div>
`;

function addAlert(){
    const elem = document.getElementById("homeCard");
    elem.insertAdjacentHTML("afterend", searchAlert);
}

if (window.location.search == "?error")
    addAlert();