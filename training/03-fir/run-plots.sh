#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
VENV_DIR="${ROOT_DIR}/training/.venv"

if [[ ! -d "${VENV_DIR}" ]]; then
  echo "Venv not found. Run training/setup-venv.sh first."
  exit 1
fi

# shellcheck disable=SC1091
source "${VENV_DIR}/bin/activate"

cmake -S "${ROOT_DIR}" -B "${ROOT_DIR}/build-training" -DENABLE_TRAINING=ON -DENABLE_TESTS=OFF
cmake --build "${ROOT_DIR}/build-training" --target kfr_training_fir -- -j6

mkdir -p "${ROOT_DIR}/svg"

"${ROOT_DIR}/build-training/training/03-fir/kfr_training_fir"

echo "Plots saved under ${ROOT_DIR}/svg"
