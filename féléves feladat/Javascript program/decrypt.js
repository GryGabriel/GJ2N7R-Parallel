function decrypt(input, text, workerCount){
    const pairs = input.split(' ');
    const pairsPerWorker = [];

    countPairsPerWorker(pairsPerWorker, pairs, workerCount);

    const workers = [];
    const decryptedText = [];

    const begin = performance.now();
    for(let i=0;i<workerCount;i++){
        const worker = new Worker('workerDecrypt.js');

        worker.onmessage = function(event) {
            const decryptedCharacter = event.data[0];
            const letterIndex = event.data[1];
            decryptedText[letterIndex] = decryptedCharacter;
        
            // Check if all workers have finished
            if(decryptedText.length === pairs.length){
              // All workers finished, join the decrypted results
              const result = document.querySelector('#displayResult');
              result.textContent = decryptedText.join('');
            }
          };

          worker.postMessage([pairs, pairsPerWorker, text, i]);

          // Add the worker to the array
          workers.push(worker);
    }
    const end = performance.now();

    console.log(`Decrypting with ${workerCount} workers took ${(end - begin)*Math.pow(10,-3)} seconds`);
}

function countPairsPerWorker(array, pairs, workerCount){
    let pairCount;
    let reminder;
    if(pairs.length < workerCount){
        workerCount = pairs.length;
        pairCount = 1;
    }else{
        pairCount = Math.floor(pairs.length / workerCount);
        reminder = pairs.length % workerCount;
    }

    for(let i=0;i<workerCount;i++){
        let pairPerWorker = 0;
        if(reminder > 0){
            pairPerWorker++;
            reminder--;
        }
        array.push(pairCount+pairPerWorker);
    }
}