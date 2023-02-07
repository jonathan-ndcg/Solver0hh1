// Toggle between main menu and game
let toggleMenu = function () {
    document.getElementById("menu").classList.toggle('hidden');
    document.getElementById("game").classList.toggle('hidden');
};

// Change state of tile
let updateTileState = function (tile, nextTileState) {
    if (arguments.length < 2)
        tile = this;

    tileState = parseInt(tile.getAttribute("data-state"));
    tile.classList.remove(`tile-${tileState}`);

    if (arguments.length < 2)
        nextTileState = (tileState + 1) % 3

    tile.setAttribute("data-state", nextTileState);
    tile.classList.add(`tile-${nextTileState}`);
}

// Append grid of specified size to specified element
let makeGrid = function (element, size) {
    element.textContent = '';
    element.style.gridTemplateColumns = `repeat(${size}, 1fr)`;
    for (let i = 0; i < size * size; i++) {
        let tile = document.createElement("div");
        tile.classList.add("tile", "tile-0");
        tile.setAttribute("data-state", 0);
        tile.addEventListener('click', updateTileState);
        element.appendChild(tile);
    }
};

// Make both grids of selected size
let makeGrids = function () {
    let size = this.getAttribute("data-size");
    let sizeInfo = document.getElementById("size-info");
    let puzzleGrid = document.getElementById("puzzle-grid");
    let solutionGrid = document.getElementById("solution-grid");

    sizeInfo.textContent = `${size} x ${size}`;
    makeGrid(puzzleGrid, size);
    makeGrid(solutionGrid, size);
    toggleMenu();
};

// Get puzzle in string form
let gridToString = function () {
    let puzzleGrid = document.getElementById("puzzle-grid");
    let strGrid = "";
    for (const tile of puzzleGrid.children) {
        strGrid += tile.getAttribute("data-state");
    }
    return strGrid;
};

let displaySolution = function () {
    let strGrid = this.responseText;
    let solutionGrid = document.getElementById("solution-grid");
    let tiles = Array.from(solutionGrid.children);
    tiles.forEach(function (tile, i) {
        updateTileState(tile, strGrid[i])
    });
};

let solve = function () {
    let strGrid = gridToString();
    // Get solution from backend
    const req = new XMLHttpRequest();
    req.addEventListener("load", displaySolution);
    req.open("GET", `http://localhost:18080/solve/${strGrid}`);
    req.send();
};

// Add event listener to each menu button to generate grid
const menuButtons = document.querySelectorAll('[data-action="makeGrids"]');
Array.from(menuButtons).forEach(function (menuButton) {
    menuButton.addEventListener('click', makeGrids);
});

// Add event listener to solve button
const solveButton = document.querySelector('[data-action="solve"]');
solveButton.addEventListener('click', solve);


// Add event listener to return button
const returnToMenuButton = document.querySelector('[data-action="returnToMenu"]');
returnToMenuButton.addEventListener('click', toggleMenu);
