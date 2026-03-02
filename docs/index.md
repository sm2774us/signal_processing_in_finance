# HFT Signal Processing Stack: Professional Manual {#mainpage}

Welcome to the official technical documentation for the **HFT Signal Processing Stack**. This manual provides a deep-dive into the architecture, implementation, and verification of a world-class, 100% production-grade HFT signal processing stack.

---

## 📖 Table of Contents (Book Chapters)

1.  @subpage introduction "Chapter 1: Introduction & Executive Overview"
2.  @subpage getting_started "Chapter 2: Getting Started & Build Instructions"
3.  @subpage requirements "Chapter 3: Engineering Requirements & Specifications"
4.  @subpage hardware_arch "Chapter 4: Hardware Layer (Silicon & ASM)"
5.  @subpage networking "Chapter 5: Network Layer (Kernel-Bypass)"
6.  @subpage signal_processing "Chapter 6: Signal Layer (State Estimation)"
7.  @subpage optimization "Chapter 7: Execution Layer (Convex Optimization)"
8.  @subpage cpp26_features "Chapter 8: C++26 Modern Feature Deep-Dive"
9.  @subpage verification "Chapter 9: Verification & Coverage Strategy"
10. @subpage benchmarking "Chapter 10: Performance Benchmarking"
11. @subpage citations "Chapter 11: Citations & Research"

---

## 🏗️ Architectural Data Flow

```text
  ┌───────────────────────────────────────────────────────────────────┐
  │                      SILICON / FPGA LAYER                         │
  │                                                                   │
  │  [Network Wire] ───► [TOE IP Core] ───► [AXI-DMA Engine]          │
  │   (AXI-Stream)      (Price Filter)      (Data Transfer)           │
  └──────────────────────────────┬────────────────────────────────────┘
                                 │
                                 │ (Zero-Copy DMA)
                                 ▼
  ┌───────────────────────────────────────────────────────────────────┐
  │                      HOST CPU / C++26 LAYER                       │
  │                                                                   │
  │  [ef_vi Descriptor Ring] ◄─── (ASM MMIO Poll) ─── [TickConsumer]  │
  │          │                                            │           │
  │          │                                            ▼           │
  │          │                                     [Kalman Filter]    │
  │          │                                            │           │
  │          ▼                                            ▼           │
  │    [Order Entry] ◄──── [Convex Optimizer] ◄──── (std::mdspan)     │
  └───────────────────────────────────────────────────────────────────┘
```

---

[Start Reading: Chapter 1: Introduction >>](introduction.html)
