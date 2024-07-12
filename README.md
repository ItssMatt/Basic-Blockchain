# About
 A simple blockchain able to manage balances, process transactions and create blocks.

# Features
 This blockchain project has the following features:
 - Storage and management for balances and nonces of every account.
 - Keccak256 encryption for account addresses and hashes.
 - Transaction processor. You can send a transaction to the pool by creating a CTransaction object.
 - Revert transaction. If a transaction fails ( by insufficient balance or overflow ), it will reject the transaction and revert the state of the accounts.
 - Blocks loader and creator. Every block is created every BLOCK_TIME seconds, it waits for a miner to submit blocks, and if there is no miner sending blocks, it will call CMiner::mineSelf().
 - A miner class that should be used when it receives blocks from miners.
 - A math class called SafeMath that handles every addition/subtraction.
 - A thread runner class that is used to create and manage every new thread.
 - A config.json file where you can add/remove/modify the starting balances of specific accounts.

# Almost complete
 The only thing this project is missing is a HTTP server that should process GET/POST requests for submitting transactions, mining blocks, getting data from the blockchain etc. I recommend BOOST.ASIO for this task!