#include "../thread/thread.h"


void mineThreadFn(void) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(Constants::BLOCK_TIME));
        std::this_thread::sleep_for(std::chrono::seconds(Constants::BLOCK_TIME / 2));
        if (true && pendingTxs.size() > 0) { // check if http server received block from a miner, if not, this condition comes in
            CMiner::mineSelf();
        }
    }
}