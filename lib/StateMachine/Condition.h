#pragma once

class Condition {
    private:
        void *to;
    public:
        Condition(void *to) {
            this->to = to;
        };

        void *getTo() {
            return to;
        };

        virtual bool isMet() = 0;
};