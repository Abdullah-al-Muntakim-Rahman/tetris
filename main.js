
const row = 20, column = 20, space = "..", brick = "[]", occupied_row = new Array(column).fill(brick), empty_row = new Array(column).fill(space);
const game_state = {
    screen: document.getElementById("screen"),
    display: "",
    points: 0,
    frame: 1,
    y_coordinate: 0,
    x_coordinate: column / 2,
    block_number: Math.floor(Math.random() * 18),
    grid: Array.from({ length: row }, () => new Array(column).fill(space)),
    occupied_coordinates: [],
    last_coordinates: [
        [0, 0],
        [0, 0],
        [0, 0],
        [0, 0],
    ]
}

const pieces = [
    {
        name: "O",
        positions: (x, y) => ({
            1: [x, y],
            2: [x + 1, y],
            3: [x + 1, y + 1],
            4: [x, y + 1],
        }),
        rotate: 0,
    },
    {
        name: "I",
        positions: (x, y) => ({
            1: [x, y],
            2: [x, y + 1],
            3: [x, y + 2],
            4: [x, y + 3],
        }),
        rotate: 2,
    },
    {
        name: "I_R1",
        positions: (x, y) => ({
            1: [x, y],
            2: [x + 1, y],
            3: [x + 2, y],
            4: [x + 3, y],
        }),
        rotate: 1,
    },
    {
        name: "S",
        positions: (x, y) => ({
            1: [x, y],
            2: [x + 1, y],
            3: [x, y + 1],
            4: [x - 1, y + 1],
        }),
        rotate: 4,
    },
    {
        name: "S_R1",
        positions: (x, y) => ({
            1: [x, y],
            2: [x, y + 1],
            3: [x + 1, y + 1],
            4: [x + 1, y + 2],
        }),
        rotate: 3,
    },
    {
        name: "Z",
        positions: (x, y) => ({
            1: [x, y],
            2: [x + 1, y],
            3: [x + 1, y + 1],
            4: [x + 2, y + 1],
        }),
        rotate: 6,
    },
    {
        name: "Z_R1",
        positions: (x, y) => ({
            1: [x, y],
            2: [x, y + 1],
            3: [x - 1, y + 1],
            4: [x - 1, y + 2],
        }),
        rotate: 5,
    },
    {
        name: "L",
        positions: (x, y) => ({
            1: [x, y],
            2: [x + 1, y + 2],
            3: [x, y + 1],
            4: [x, y + 2],
        }),
        rotate: 8,
    },
    {
        name: "L_R1",
        positions: (x, y) => ({
            1: [x, y],
            2: [x + 1, y],
            3: [x + 2, y],
            4: [x, y + 1],
        }),
        rotate: 9,
    },
    {
        name: "L_R2",
        positions: (x, y) => ({
            1: [x, y],
            2: [x + 1, y],
            3: [x + 1, y + 1],
            4: [x + 1, y + 2],
        }),
        rotate: 10,
    },
    {
        name: "L_R3",
        positions: (x, y) => ({
            1: [x, y],
            2: [x, y + 1],
            3: [x - 1, y + 1],
            4: [x - 2, y + 1],
        }),
        rotate: 7,
    },
    {
        name: "J",
        positions: (x, y) => ({
            1: [x, y],
            2: [x, y + 1],
            3: [x, y + 2],
            4: [x - 1, y + 2],
        }),
        rotate: 12,
    },
    {
        name: "J_R1",
        positions: (x, y) => ({
            1: [x, y],
            2: [x, y + 1],
            3: [x + 1, y + 1],
            4: [x + 2, y + 1],
        }),
        rotate: 13,
    },
    {
        name: "J_R2",
        positions: (x, y) => ({
            1: [x, y],
            2: [x + 1, y],
            3: [x + 1, y + 1],
            4: [x + 1, y + 2],
        }),
        rotate: 14,
    },
    {
        name: "J_R3",
        positions: (x, y) => ({
            1: [x, y],
            2: [x + 1, y],
            3: [x + 2, y],
            4: [x + 2, y + 1],
        }),
        rotate: 11,
    },
    {
        name: "T",
        positions: (x, y) => ({
            1: [x, y],
            2: [x + 1, y],
            3: [x + 2, y],
            4: [x + 1, y + 1],
        }),
        rotate: 16,
    },
    {
        name: "T_R1",
        positions: (x, y) => ({
            1: [x, y],
            2: [x - 1, y + 1],
            3: [x, y + 1],
            4: [x, y + 2],
        }),
        rotate: 17,
    },
    {
        name: "T_R2",
        positions: (x, y) => ({
            1: [x, y],
            2: [x, y + 1],
            3: [x + 1, y + 1],
            4: [x - 1, y + 1],
        }),
        rotate: 18,
    },
    {
        name: "T_R3",
        positions: (x, y) => ({
            1: [x, y],
            2: [x, y + 1],
            3: [x + 1, y + 1],
            4: [x, y + 2],
        }),
        rotate: 15,
    },
];

function newBlock() {
    game_state.occupied_coordinates.push(game_state.last_coordinates[1]);
    game_state.occupied_coordinates.push(game_state.last_coordinates[2]);
    game_state.occupied_coordinates.push(game_state.last_coordinates[3]);
    game_state.occupied_coordinates.push(game_state.last_coordinates[4]);
    game_state.y_coordinate = 0;
    game_state.x_coordinate = column / 2 - 1;
    game_state.block_number = Math.floor(Math.random() * 18);
}

function detectCollision() {
    let current_coordinates = pieces[game_state.block_number].positions(game_state.x_coordinate, game_state.y_coordinate);
    for (let i in game_state.occupied_coordinates){
        for (let j in current_coordinates){
            if(current_coordinates[j][0] == game_state.occupied_coordinates[i][0] && current_coordinates[j][1] == game_state.occupied_coordinates[i][1]){
                return true;
            }
        }
    }
}

function check_boundary(left_boundary, right_boundary, vertical_boundary) {
    if (game_state.x_coordinate < left_boundary) {
        game_state.x_coordinate = column - right_boundary;
        if(detectCollision()){
            game_state.x_coordinate = left_boundary;
        }
    } else if (game_state.x_coordinate > column - right_boundary) {
        game_state.x_coordinate = left_boundary;
        if(detectCollision()){
            game_state.x_coordinate = column - right_boundary;
        }
    } else if (game_state.y_coordinate > row - vertical_boundary) {
        newBlock();
    }
}

function boundary() {
    switch (game_state.block_number) {
        case 0:
            check_boundary(0, 2, 2);
            break;
        case 1:
            check_boundary(0, 1, 4);
            break;
        case 2:
            check_boundary(0, 4, 1);
            break;
        case 3:
            check_boundary(1, 2, 2);
            break;
        case 4:
            check_boundary(0, 2, 3);
            break;
        case 5:
            check_boundary(0, 3, 2);
            break;
        case 6:
            check_boundary(1, 1, 3);
            break;
        case 7:
            check_boundary(0, 2, 3);
            break;
        case 8:
            check_boundary(0, 3, 2);
            break;
        case 9:
            check_boundary(0, 2, 3);
            break;
        case 10:
            check_boundary(2, 1, 2);
            break;
        case 11:
            check_boundary(1, 1, 3);
            break;
        case 12:
            check_boundary(0, 3, 2);
            break;
        case 13:
            check_boundary(0, 2, 3);
            break;
        case 14:
            check_boundary(0, 3, 2);
            break;
        case 15:
            check_boundary(0, 3, 2);
            break;
        case 16:
            check_boundary(1, 1, 3);
            break;
        case 17:
            check_boundary(1, 2, 2);
            break;
        case 18:
            check_boundary(0, 2, 3);
            break;
        default:
            break;
    }
}

function clean() {
    game_state.display = "";
    try {
        for (let i in game_state.last_coordinates) {
            game_state.grid[game_state.last_coordinates[i][1]][game_state.last_coordinates[i][0]] = space;
        }
    } catch (error) {
        console.log(error);
    }
}

function paint() {
    try {
        for(let j in game_state.occupied_coordinates){
            game_state.grid[game_state.occupied_coordinates[j][1]][game_state.occupied_coordinates[j][0]] = brick;
        }
        for (let i in game_state.last_coordinates) {
            game_state.grid[game_state.last_coordinates[i][1]][game_state.last_coordinates[i][0]] = brick;
        }
    } catch (error) {
        console.log(game_state.block_number);
    }
}

function assign() {
    clean();
    try {
        var coordinates = pieces[game_state.block_number].positions(game_state.x_coordinate, game_state.y_coordinate);
    } catch (error) {
        console.log(error);
    }
    game_state.last_coordinates = coordinates;
    paint();
}

function move_right() {
    game_state.x_coordinate += 1;
    if(detectCollision()){
        game_state.x_coordinate -= 1;
    }
    assign();
}

function move_left() {
    game_state.x_coordinate -= 1;
    if(detectCollision()){
        game_state.x_coordinate += 1;
    }
    assign();
}

function rotate() {
    game_state.block_number = pieces[game_state.block_number].rotate;
    if(detectCollision()){
        let not_rotate = {0:0,1:2,2:1,3:4,4:3,5:6,6:5,7:10,8:7,9:8,10:9,11:14,12:11,13:12,14:13,15:18,16:15,17:16,18:17,};
        game_state.block_number = not_rotate[game_state.block_number];
    }
    assign();
}

document.onkeydown = function (e) {
    switch (e.key) {
        case "ArrowLeft":
            move_left();
            break;
        case "ArrowRight":
            move_right();
            break;
        case " ":
            rotate();
            break;
    }
};

function update() {
    if (game_state.frame == 5) {
        game_state.y_coordinate += 1;
        game_state.frame = 1;
    } else {
        game_state.frame += 1;
    }
    if(detectCollision()){
        newBlock();
    }
    boundary();
    assign();
    let temporary = 0;
    for (var i = 0; i < row; i++) {
        if(JSON.stringify(game_state.grid[i]) == JSON.stringify(occupied_row)){
            for (let q = 0; q < column; q++){
                let index = game_state.occupied_coordinates.findIndex(row => JSON.stringify(row) === JSON.stringify([i,q]));
                if (index !== -1) {
                    game_state.occupied_coordinates.splice(index, 1);
                }
            }
            for (let p = i; p > 0; p--){
                game_state.grid[p] = game_state.grid[p-1];
            }
            game_state.grid[0] = empty_row;
            temporary += 1;
            if(temporary == 4){
                game_state.points += column*7;
                temporary=0;
            }else{
                game_state.points += column;
            }
        }
        for (var j = 0; j < column; j++) {
            game_state.display += game_state.grid[i][j];
        }
        if(temporary != 0){
            temporary -= 1;
        }
        game_state.display += "</br>";
    }
    game_state.screen.innerHTML = "<p>" + game_state.display + "</p>";
}
setInterval(update, 50);